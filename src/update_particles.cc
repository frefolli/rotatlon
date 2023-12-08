#include <cmath>
#include <rotatlon/update_particles.hh>
#include <rotatlon/config.hh>

inline float_t delta_x(Particle& a, Particle& b) {
  return a.position.x - b.position.x;
}

inline float_t delta_y(Particle& a, Particle& b) {
  return a.position.y - b.position.y;
}

inline float_t delta_z(Particle& a, Particle& b) {
  return a.position.z - b.position.z;
}

inline float_t xy_angle(float_t dx, float_t dy) {
  return atan2(dy, dx);
}

inline float_t z_angle(float_t dx_2, float_t dy_2, float_t dz) {
  return atan(sqrt(dx_2 + dy_2));
}

inline void move(Particle& particle) {
  particle.position.x += particle.speed.x;
  particle.position.y += particle.speed.y;
  particle.position.z += particle.speed.z;
}

inline void accelerate(Particle& particle, float_t a, float_t phi, float_t theta) {
  particle.speed.x -= a * cos(phi) * sin(theta);
  particle.speed.y -= a * sin(phi) * sin(theta);
  particle.speed.z -= a * cos(theta);
}

void UpdateParticles(std::vector<Particle>& particles) {
  size_t length = particles.size();
  for (size_t i = 0; i < length; i++) {
    for (size_t j = i+1; j < length; j++) {
      float_t dx = delta_x(particles[i], particles[j]);     // dx = Pi.x - Pj.x
      float_t dy = delta_y(particles[i], particles[j]);     // dy = Pi.y - Pj.y
      float_t dz = delta_z(particles[i], particles[j]);     // dz = Pi.z - Pj.z

      float_t dx_2 = pow(dx, 2);                            // dx_2 = dx^2
      float_t dy_2 = pow(dy, 2);                            // dy_2 = dy^2
      float_t dz_2 = pow(dz, 2);                            // dz_2 = dz^2

      float_t d_2 = dx_2 + dy_2 + dz_2;                     // d_2 = dx^2 + dy^2 + dz^2
      
      float_t phi_i = xy_angle(dx, dy);                     // phi = xz-angle(Pi, Pj)
      float_t theta_i = z_angle(dx_2, dy_2, dz);            // theta = z-angle(Pi, Pj)
      
      float_t phi_j = xy_angle(-dx, -dy);                   // phi = xz-angle(Pj, Pi)
      float_t theta_j = z_angle(dx_2, dy_2, -dz);           // theta = z-angle(Pj, Pi)

                                                            // dtime = 1 / FramesPerSecond
      float_t a_i = particles[j].mass / d_2;                // a_i = Pj.mass / d^2
      float_t a_j = particles[i].mass / d_2;                // a_j = Pi.mass / d^2

      accelerate(particles[i], a_i, phi_i, theta_i);
      accelerate(particles[j], a_j, phi_j, theta_j);
    }
  }

  for (size_t i = 0; i < length; i++) {
    move(particles[i]);
  }
}
