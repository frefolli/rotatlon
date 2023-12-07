#include <rotatlon/v2.hh>

std::ostream& operator<<(std::ostream& out, V2 v2) {
  out << "(" << v2.x << ", " << v2.y << ")";
  return out;
}
