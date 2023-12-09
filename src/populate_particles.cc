#include <rotatlon/populate_particles.hh>
#include <rotatlon/config.hh>

size_t SIZE = 15;

void PopulateParticles(std::vector<Particle>& particles) {
  for (size_t i = 0; i < SIZE; i++) {
    double mass = 0.0f;
    V3 position = { (double) (std::rand() % WIDTH),
                    (double) (std::rand() % HEIGHT),
                    (double) (std::rand() % HEIGHT) };
    V3 speed = { (double) (std::rand() % 4 - 2),
                 (double) (std::rand() % 4 - 2),
                 (double) (std::rand() % 4 - 2) };
    int radius = std::rand() % 10 + 1;
    Color color = {
      (unsigned char) (std::rand() % 256),
      (unsigned char) (std::rand() % 256),
      (unsigned char) (std::rand() % 256),
      (unsigned char) (std::rand() % 256)
    };

    Particle particle = newParticle(mass, position, speed, radius, color);
    particles.push_back(particle);
  }
}
