#ifndef ROTATLON_V3_HH
#define ROTATLON_V3_HH

#include <cmath>
#include <ostream>

typedef struct {
  float_t x;
  float_t y;
  float_t z;
} V3;

std::ostream& operator<<(std::ostream& out, V3 v3);

#endif
