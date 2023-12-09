#include <cmath>
#include <rotatlon/update_particles.hh>
#include <rotatlon/config.hh>

inline double delta_x(Particle& a, Particle& b) {
  return a.position.x - b.position.x;
}

inline double delta_y(Particle& a, Particle& b) {
  return a.position.y - b.position.y;
}

inline double delta_z(Particle& a, Particle& b) {
  return a.position.z - b.position.z;
}

inline double xy_angle(double dx, double dy) {
  return atan2(dy, dx);
}

inline double z_angle(double d, double dz) {
  return atan2(dz, d);
}

inline void move(Particle& particle) {
  particle.position.x += particle.speed.x * DTIME;
  particle.position.y += particle.speed.y * DTIME;
  particle.position.z += particle.speed.z * DTIME;
}

inline void accelerate(Particle& particle) {
  particle.speed.x += particle.acceleration.x * DTIME;
  particle.speed.y += particle.acceleration.y * DTIME;
  particle.speed.z += particle.acceleration.z * DTIME;
}

inline void apply_force(Particle& particle, double a, double phi, double theta) {
  particle.acceleration.x -= a * cos(phi);
  particle.acceleration.y -= a * sin(phi);
  particle.acceleration.z -= a * sin(theta);
}

void UpdateParticles(std::vector<Particle>& particles) {
  size_t length = particles.size();

  for (size_t i = 0; i < length; i++) {
    particles[i].acceleration = {0.0f, 0.0f, 0.0f};
  }
  for (size_t i = 0; i < length; i++) {
    for (size_t j = i+1; j < length; j++) {
      double dx = delta_x(particles[i], particles[j]);     // dx = Pi.x - Pj.x
      double dy = delta_y(particles[i], particles[j]);     // dy = Pi.y - Pj.y
      double dz = delta_z(particles[i], particles[j]);     // dz = Pi.z - Pj.z

      double dx_2 = pow(dx, 2);                            // dx_2 = dx^2
      double dy_2 = pow(dy, 2);                            // dy_2 = dy^2
      double dz_2 = pow(dz, 2);                            // dz_2 = dz^2

      double d_2 = dx_2 + dy_2 + dz_2;                     // d_2 = dx^2 + dy^2 + dz^2
      double d = sqrt(d_2);                     // d_2 = dx^2 + dy^2 + dz^2
      
      double phi_i = xy_angle(dx, dy);                     // phi = xz-angle(Pi, Pj)
      double theta_i = z_angle(d, dz);            // theta = z-angle(Pi, Pj)
      
      double phi_j = xy_angle(-dx, -dy);                   // phi = xz-angle(Pj, Pi)
      double theta_j = z_angle(d, -dz);           // theta = z-angle(Pj, Pi)

                                                            // DTIME = 1 / FramesPerSecond
      double a_i = particles[j].mass / d_2;                // a_i = Pj.mass / d^2
      double a_j = particles[i].mass / d_2;                // a_j = Pi.mass / d^2

      apply_force(particles[i], a_i, phi_i, theta_i);
      apply_force(particles[j], a_j, phi_j, theta_j);
    }
  }

  for (size_t i = 0; i < length; i++) {
    accelerate(particles[i]);
    move(particles[i]);
  }
}
