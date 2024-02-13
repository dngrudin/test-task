
#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <set>
#include <vector>

namespace top5 {
/**
 * @brief Input and output types.
 */

using Value = std::uint16_t;
using Matrix = std::vector<Value>;
using Top5Result = std::vector<std::set<Value>>;

} // namespace top5

#endif // TYPES_H