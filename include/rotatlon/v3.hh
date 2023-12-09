#ifndef ROTATLON_V3_HH
#define ROTATLON_V3_HH

#include <cmath>
#include <ostream>

typedef struct {
  double x;
  double y;
  double z;
} V3;

std::ostream& operator<<(std::ostream& out, V3 v3);

#endif
