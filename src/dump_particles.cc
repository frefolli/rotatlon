#include <rotatlon/dump_particles.hh>
#include <rotatlon/config.hh>
#include <stdexcept>

void DumpHeader(std::ostream& out) {
  out << "particle, px, py, pz, sx, sy, sz, ax, ay, az" << std::endl;
}

void DumpParticles(std::ostream& out, std::vector<Particle>& particles) {
  size_t length = particles.size();
  for (size_t i = 0; i < length; i++) {
    if (particles[i].position.x < -BOUNDARY || particles[i].position.x > BOUNDARY)
      continue;
    if (particles[i].position.y < -BOUNDARY || particles[i].position.y > BOUNDARY)
      continue;
    if (particles[i].position.z < -BOUNDARY || particles[i].position.z > BOUNDARY)
      continue;
    out << i
      << ", " << particles[i].position.x
      << ", " << particles[i].position.y
      << ", " << particles[i].position.z
      << ", " << particles[i].speed.x
      << ", " << particles[i].speed.y
      << ", " << particles[i].speed.z
      << ", " << particles[i].acceleration.x
      << ", " << particles[i].acceleration.y
      << ", " << particles[i].acceleration.z
      << std::endl;
  }
}
