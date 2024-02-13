
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>

#include "top5.hpp"

namespace detail {

static constexpr std::size_t MatrixSize = 5000;
static constexpr std::size_t MaxCountThreads = 5;

} // namespace detail

top5::Value randBetween(top5::Value min, top5::Value max);
void fillMatrix(top5::Matrix &matrix, top5::Value min, top5::Value max);
void print(const top5::Top5Result &top);

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  top5::Matrix matrix(detail::MatrixSize * detail::MatrixSize);
  fillMatrix(matrix, 0, top5::getMaxAvalibleValue());

  for (std::size_t i = 1; i <= detail::MaxCountThreads; ++i) {
    std::cout << "Count threads: " << i << "\n";

    auto start = std::chrono::steady_clock::now();
    auto top5 = top5::getTop5(matrix, i);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " s\n";

    print(top5);
  }

  return 0;
}

top5::Value randBetween(top5::Value min, top5::Value max) {
  return static_cast<top5::Value>(min + std::rand() % (max - min + 1));
}

void fillMatrix(top5::Matrix &matrix, top5::Value min, top5::Value max) {
  for (auto &item : matrix) {
    item = randBetween(min, max);
  }
}

void print(const top5::Top5Result &top) {
  for (const auto &item : top) {
    std::copy(std::begin(item), std::end(item), std::ostream_iterator<top5::Value>(std::cout, " "));
    std::cout << '\n';
  }
}