#ifndef ROTATLON_PARTICLE_HH
#define ROTATLON_PARTICLE_HH

#include <cmath>
#include <rotatlon/v3.hh>
#include <ostream>
#include <raylib.h>

typedef struct {
  float_t mass;
  V3 position;
  V3 speed;
  V3 acceleration;
  int radius;
  Color color;
} Particle;

Particle newParticle(float_t mass,
                     V3 position,
                     V3 speed,
                     int radius,
                     Color color);

std::ostream& operator<<(std::ostream& out, Particle particle);

#endif
