#include "coordinates.h"

std::ostream &operator<<(std::ostream &stream, const Coordinates &value) {
  stream << value.x << " " << value.y;

  return stream;
}

bool operator<(const Coordinates &lhs, const Coordinates &rhs) {
  return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}
