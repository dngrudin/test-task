#pragma once

#include <cstddef>

struct PayloadRange {
  bool isValid() const { return end > begin; }

  std::size_t begin = 0;
  std::size_t end = 0;
};