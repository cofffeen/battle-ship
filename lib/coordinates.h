#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <iostream>

struct Coordinates {
  uint64_t x;
  uint64_t y;
};

std::ostream &operator<<(std::ostream &stream, const Coordinates &value);
bool operator<(const Coordinates &lhs, const Coordinates &rhs);
