#ifndef BLOCK_INFO_H
#define BLOCK_INFO_H

#include <string>

std::size_t get_block_number(const std::string &hash);

std::size_t get_block_size(const std::string &hash);

#endif // BLOCK_INFO_H