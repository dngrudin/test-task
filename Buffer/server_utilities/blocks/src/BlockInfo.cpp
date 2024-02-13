
#include <charconv>

#include "BlockInfo.hpp"

namespace detail {

static constexpr std::size_t BLOCK_SIZE = 4 * 1024;
static constexpr std::size_t BLOCKS_COUNT = (1024 * 1024 * 1024) / BLOCK_SIZE;

} // namespace detail

std::size_t get_block_number(const std::string &hash) {
  /// implementation for testing

  std::size_t number{};
  static_cast<void>(
      std::from_chars(hash.data(), hash.data() + hash.size(), number));
  return number % detail::BLOCKS_COUNT;
}

std::size_t get_block_size(const std::string &hash) {
  /// implementation for testing

  std::size_t number{};
  static_cast<void>(
      std::from_chars(hash.data(), hash.data() + hash.size(), number));
  if (number % 2) {
    return detail::BLOCK_SIZE / 3;
  } else if (number % 3) {
    return detail::BLOCK_SIZE / 5;
  }
  return detail::BLOCK_SIZE;
}
