#include <rotatlon/particle.hh>

std::ostream& operator<<(std::ostream& out, Particle particle) {
  out << particle.mass << " | " << particle.position << " | " << particle.speed;
  return out;
}
