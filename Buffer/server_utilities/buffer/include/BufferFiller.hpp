#ifndef BUFFER_FILLER_H
#define BUFFER_FILLER_H

#include <memory>
#include <set>
#include <string>

class FileReader;

enum class BlockSizeFormat { Empty, BigEndian, LittleEndian };

class BufferFiller {
public:
  struct Result {
    std::size_t fillBytes;
    std::size_t countBlocks;
  };

  BufferFiller(std::shared_ptr<FileReader> reader);

  void setBlockSize(std::size_t blockSize);
  std::size_t getBlockSize() const;

  void setBlockSizeFormat(BlockSizeFormat blockSizeFormat);
  BlockSizeFormat getBlockSizeFormat() const;

  Result fill(const std::set<std::string> &hashs, char *buffer,
              std::size_t bufferSize);

private:
  union BlockSizeToBytes {
    std::uint32_t in;
    char out[2];
  };

  struct Block {
    Block(std::size_t blockNumber, std::size_t blockPosition,
          std::size_t blockSize)
        : number(blockNumber), position(blockPosition), size(blockSize) {}

    std::size_t number;   /// block number in file
    std::size_t position; /// block position in the output byte sequence
    std::size_t size;     /// block data size
  };

  char *fillBlockSize(char *buffer, std::size_t blockSize);

  std::shared_ptr<FileReader> mReader;
  std::size_t mBlockSize;
  BlockSizeFormat mBlockSizeFormat;
};

#endif // BUFFER_FILLER_H