
#include <algorithm>
#include <cstring>
#include <vector>

#include "BlockInfo.hpp"

#include "BufferFiller.hpp"
#include "FileReader.hpp"

namespace detail {

static constexpr std::size_t DEFAULT_BLOCK_SIZE = 16 * 1024;

}

namespace {
BlockSizeFormat getDefaultBlockSizeFormat() {
  const uint16_t x = 0x0001;
  return *((uint8_t *)&x) ? BlockSizeFormat::LittleEndian
                          : BlockSizeFormat::BigEndian;
}
} // namespace

BufferFiller::BufferFiller(std::shared_ptr<FileReader> reader)
    : mReader(reader), mBlockSize(detail::DEFAULT_BLOCK_SIZE),
      mBlockSizeFormat(getDefaultBlockSizeFormat()) {}

void BufferFiller::setBlockSize(std::size_t blockSize) {
  if (blockSize > 0) {
    mBlockSize = blockSize;
  }
}

std::size_t BufferFiller::getBlockSize() const { return mBlockSize; }

void BufferFiller::setBlockSizeFormat(BlockSizeFormat blockSizeFormat) {
  mBlockSizeFormat = blockSizeFormat;
}

BlockSizeFormat BufferFiller::getBlockSizeFormat() const {
  return mBlockSizeFormat;
}

BufferFiller::Result BufferFiller::fill(const std::set<std::string> &hashs,
                                        char *buffer, std::size_t bufferSize) {
  /// calculate the number of bytes for one block, taking into account the
  /// memory for the data size in the block
  const std::size_t extBlockSize =
      mBlockSize + (mBlockSizeFormat != BlockSizeFormat::Empty
                        ? sizeof(BlockSizeToBytes)
                        : 0);

  /// calculate the number of blocks that can be stored in the buffer
  const std::size_t maxReadBlocks =
      std::min(hashs.size(), bufferSize / extBlockSize);

  /// create a list of blocks needed for reading (with additional information)
  std::vector<Block> blocks{};
  blocks.reserve(hashs.size());
  std::size_t index = 0;
  for (const auto &hash : hashs) {
    blocks.emplace_back(get_block_number(hash), index, get_block_size(hash));
    index++;

    if (index == maxReadBlocks) {
      break;
    }
  }

  /// sort the blocks so that they are read in the order they are placed in the
  /// file (by block number)
  std::sort(std::begin(blocks), std::end(blocks),
            [](const auto &l, const auto &r) {
              return (l.number == r.number) ? l.number < r.number
                                            : l.position < r.position;
            });

  /// fill buffer with data from blocks
  for (const auto &block : blocks) {
    bool isNeedClearBuffer = true;
    if (block.size > 0) {
      /// write to the buffer the size of the data in the block
      auto *beginDataPotition =
          fillBlockSize(buffer + block.position * extBlockSize, block.size);
      /// read block into buffer
      isNeedClearBuffer = !mReader->read(
          beginDataPotition, block.number * extBlockSize, mBlockSize);
    }

    if (isNeedClearBuffer) {
      /// if the block is empty or an error occurred while reading the block
      std::memset(buffer + block.position * extBlockSize, 0, extBlockSize);
    }
  }

  /// return the number of bytes written to the buffer and the number of blocks
  /// read
  return {maxReadBlocks * extBlockSize, maxReadBlocks};
}

char *BufferFiller::fillBlockSize(char *buffer, std::size_t blockSize) {
  char *bufferOffset = buffer;

  if (mBlockSizeFormat != BlockSizeFormat::Empty) {
    BlockSizeToBytes toBytes{};
    toBytes.in = static_cast<std::uint32_t>(blockSize);

    if (getDefaultBlockSizeFormat() == mBlockSizeFormat) {
      *buffer = toBytes.out[0];
      *(buffer + 1) = toBytes.out[1];
    } else {
      *buffer = toBytes.out[1];
      *(buffer + 1) = toBytes.out[0];
    }

    bufferOffset += sizeof(BlockSizeToBytes);
  }

  return bufferOffset;
}