#include <rotatlon/particle.hh>

Particle newParticle(float_t mass,
                     V3 position,
                     V3 speed,
                     int radius,
                     Color color) {
    return {
        mass,
        position,
        speed,
        {0, 0, 0},
        radius,
        color
    }
}

std::ostream& operator<<(std::ostream& out, Particle particle) {
  out << particle.position << ", " << particle.speed;
  return out;
}
