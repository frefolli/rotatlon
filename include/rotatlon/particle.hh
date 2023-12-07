#ifndef ROTATLON_PARTICLE_HH
#define ROTATLON_PARTICLE_HH

#include <cmath>
#include <rotatlon/v3.hh>
#include <ostream>

typedef struct {
  float_t mass;
  V3 position;
  V3 speed;
} Particle;

std::ostream& operator<<(std::ostream& out, Particle particle);

#endif
