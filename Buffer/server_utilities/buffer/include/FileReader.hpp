#ifndef FILE_READER_H
#define FILE_READER_H

#include <filesystem>
#include <fstream>

enum FileType { Binary, Text };

class FileReader {
public:
  FileReader(std::filesystem::path filePath, FileType type);
  ~FileReader();

  bool open();
  void close();

  bool read(char *buffer, std::size_t offset, std::size_t size);

private:
  std::ifstream mFile;
  std::filesystem::path mFilePath;
  FileType mType;
};

#endif // FILE_READER_H