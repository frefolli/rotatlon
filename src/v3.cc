#include <rotatlon/v3.hh>

std::ostream& operator<<(std::ostream& out, V3 v3) {
  out << "(" << v3.x << ", " << v3.y << ", " << v3.z << ")";
  return out;
}
