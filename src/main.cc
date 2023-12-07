#include <raylib.h>
#include <ctime>
#include <cstring>
#include <random>
#include <stdexcept>
#include <iostream>
#include <cmath>

#include <rotatlon/particle.hh>

size_t WIDTH = 1366;
size_t HEIGHT = 768;
size_t RADIUS = 5;
bool PAUSED = false;

inline float_t distance(V3& a, V3& b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

inline float_t xy_angle(V3& a, V3& b) {
  return atan2((a.y - b.y), (a.x - b.x));
}

inline float_t z_angle(V3& a, V3& b) {
  return atan(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

inline float_t newton(Particle& a, Particle& b) {
  return (a.mass * b.mass) / pow(distance(a.position, b.position), 2);
}

inline void apply_force(Particle& a, Particle& b, float_t f) {
  float_t phi = xy_angle(a.position, b.position);

  float_t f_a = f / a.mass;
  a.speed.x -= f_a * cos(phi);
  a.speed.y -= f_a * sin(phi);
  a.speed.z -= f_a * 0;
}

inline void apply_forces(Particle& a, Particle& b) {
  float_t f = newton(a, b);
  apply_force(a, b, f);
  apply_force(b, a, f);
}

inline void move(Particle& a) {
  a.position.x += a.speed.x;
  a.position.y += a.speed.y;
  a.position.z += a.speed.z;
}

inline void UpdateParticles(Particle &a, Particle &b) {
  apply_forces(a, b);
  move(a);
  move(b);
}

inline void DrawParticles(Particle &a, Particle &b, bool trace) {
  Color a_color = GREEN;
  Color b_color = RED;
  int radius = RADIUS;
  if (trace) {
    a_color = ORANGE;
    b_color = LIME;
    radius = 2;
  }
  DrawCircle((int) a.position.x, (int) a.position.y, radius, a_color);
  DrawCircle((int) b.position.x, (int) b.position.y, radius, b_color);
}

int realMain(int argc, char** args) {
  // --------------------------------------------------------------------
  // INIT
  Particle a = {1000, {700,500,0}, {0,0,0}};
  Particle b = {0.3, {200,200,0}, {1,0,0}};
  // --------------------------------------------------------------------
  // INIT WINDOW
  InitWindow(WIDTH, HEIGHT, "dioimperatoresalvini");
  if (!IsWindowReady()) {
    throw std::runtime_error("Unable to initialize window");
  }

  SetTargetFPS(60);
  BeginDrawing();
  ClearBackground(WHITE);
  EndDrawing();
  // --------------------------------------------------------------------
  // REL
  while (!WindowShouldClose()) {
    BeginDrawing();
    DrawParticles(a, b, true);
    if(IsKeyPressed(KEY_LEFT)) {
      PAUSED = !PAUSED;
    } else if (!PAUSED) {
      UpdateParticles(a, b);
    }
    DrawParticles(a, b, false);
    EndDrawing();
  }
  // --------------------------------------------------------------------
  // DELETE
  // --------------------------------------------------------------------
  CloseWindow();
  return 0;
}

int main(int argc, char** args) {
  char* AC_RED = "\u001b[31m";
  char* AC_RESET = "\u001b[0m";
  try {
    return realMain(argc, args);
  } catch(std::exception& error) {
    std::printf("%sERROR:%s %s\n", AC_RED, AC_RESET, error.what());
    return 1;
  }
}
