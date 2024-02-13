
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "BufferFiller.hpp"
#include "FileReader.hpp"

int main() {
  const std::set<std::string> hashs{
      "1", "22", "23", "35", "33", "995",
  };

  std::vector<char> buffer(10 * 1024 * 1024);

  auto fileReader =
      std::make_shared<FileReader>("test_data_file", FileType::Binary);
  if (fileReader->open()) {
    auto bufferFiller = std::make_shared<BufferFiller>(fileReader);
    bufferFiller->setBlockSize(32 * 1024);
    bufferFiller->setBlockSizeFormat(BlockSizeFormat::BigEndian);

    auto [bytes, count] =
        bufferFiller->fill(hashs, buffer.data(), buffer.size());
    std::cout << "fillBytes=" << bytes << " countBlocks=" << count << '\n';

    /// implementation for testing
    std::ofstream out("out", std::ios_base::out | std::ios_base::binary);
    out.write(buffer.data(), bytes);
    out.close();
  } else {
    std::cerr << "Data source not found\n";
  }

  return 0;
}