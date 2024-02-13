
#include "FileReader.hpp"

FileReader::FileReader(std::filesystem::path filePath, FileType type)
    : mFilePath(filePath), mType(type) {}

FileReader::~FileReader() { close(); }

bool FileReader::open() {
  bool result = false;
  if (!mFile.rdbuf()->is_open()) {
    auto *filebuf = mFile.rdbuf()->open(
        mFilePath,
        (mType == FileType::Binary ? (std::ios_base::in | std::ios_base::binary)
                                   : std::ios_base::in));
    result = (filebuf != nullptr);
  }

  return result;
}

void FileReader::close() {
  if (mFile.rdbuf()->is_open()) {
    mFile.rdbuf()->close();
  }
}

bool FileReader::read(char *buffer, std::size_t offset, std::size_t size) {
  bool result = false;
  try {
    result = mFile.seekg(offset).read(buffer, size).good();
  } catch (const std::ios_base::failure &e) {
  }
  return result;
}