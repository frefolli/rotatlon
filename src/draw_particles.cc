#include <rotatlon/draw_particles.hh>
#include <rotatlon/config.hh>
#include <raylib.h>

size_t FACTOR = 2;

void DrawParticles(std::vector<Particle>& particles) {
  size_t length = particles.size();
  for (size_t i = 0; i < length; i++) {
    #ifdef MODE_3D
      DrawSphere(particles[i].position, particles[i].radius, particles[i].color);
    #else
      int x = (particles[i].position.x) - WINDOW_SHIFT_X;
      int y = (particles[i].position.y) - WINDOW_SHIFT_Y;
      DrawCircle(x, y, particles[i].radius, particles[i].color);
    #endif
  }
}
