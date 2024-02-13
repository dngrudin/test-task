#ifndef DATA_PULL_HPP
#define DATA_PULL_HPP

#include <cstddef>
#include <stdint.h>
#include <vector>

class DataPull {
public:
  DataPull(size_t size);

  void generate();

  const std::vector<int16_t> &get(size_t index) const;
  size_t count() const;

private:
  static void fill(std::vector<int16_t> &data);

  std::vector<std::vector<int16_t> > mDataPull;
};

#endif // DATA_PULL_HPP