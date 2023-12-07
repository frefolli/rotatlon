#ifndef ROTATLON_V2_HH
#define ROTATLON_V2_HH

#include <cmath>
#include <ostream>

typedef struct {
  float_t x;
  float_t y;
} V2;

std::ostream& operator<<(std::ostream& out, V2 v2);

#endif
