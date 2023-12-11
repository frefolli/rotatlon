#include <rotatlon/draw_particles.hh>
#include <rotatlon/config.hh>
#include <raylib.h>

size_t FACTOR = 2;

void DrawParticles(std::vector<Particle>& particles) {
  size_t length = particles.size();
  for (size_t i = 0; i < length; i++) {
    #ifdef MODE_3D
      DrawSphere({(float) particles[i].position.x, (float) particles[i].position.z, (float) particles[i].position.y}, particles[i].radius, particles[i].color);
    #else
      DrawCircle(particles[i].position.x, particles[i].position.y, particles[i].radius, particles[i].color);
    #endif
  }
}
