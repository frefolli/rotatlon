#include <rotatlon/draw_particles.hh>
#include <raylib.h>

size_t FACTOR = 2;

void DrawParticles(std::vector<Particle>& particles) {
  size_t length = particles.size();
  for (size_t i = 0; i < length; i++)
    DrawCircle((int) (particles[i].position.x / FACTOR), (int) (particles[i].position.y / FACTOR), (int) (particles[i].radius / FACTOR), particles[i].color);
}
