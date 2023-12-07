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
  return atan((a.y - b.y) / (a.x - b.x));
}

inline float_t yz_angle(V3& a, V3& b) {
  return atan((a.z - b.z) / (a.y - b.y));
}

inline float_t newton(Particle& a, Particle& b) {
  return (a.mass * b.mass) / pow(distance(a.position, b.position), 2);
}

inline void apply_force(Particle& a, Particle& b) {
  float_t phi = xy_angle(a.position, b.position);
  float_t theta = yz_angle(a.position, b.position);
  float_t f = newton(a, b);
  
  float_t f_a = f / a.mass;
  a.speed.x += f_a * cos(phi) * sin(theta);
  a.speed.y += f_a * sin(phi) * sin(theta);
  a.speed.z += f_a * cos(theta);

  float_t f_b = f / b.mass;
  b.speed.x -= f_b * cos(phi) * sin(theta);
  b.speed.y -= f_b * sin(phi) * sin(theta);
  b.speed.z -= f_b * cos(theta);
}

inline void move(Particle& a) {
  a.position.x += a.speed.x;
  a.position.y += a.speed.y;
  a.position.z += a.speed.z;
}

inline void UpdateParticles(Particle &a, Particle &b) {
  apply_force(a, b);
  move(a);
  move(b);
}

inline void DrawParticles(Particle &a, Particle &b) {
  DrawCircle((int) a.position.x, (int) a.position.y, RADIUS, RED);
  DrawCircle((int) b.position.x, (int) b.position.y, RADIUS, GREEN);
}

int realMain(int argc, char** args) {
  // --------------------------------------------------------------------
  // INIT
  Particle a = {200, {0,0,0}, {0,0,0}};
  Particle b = {0.3, {-10,0,0}, {1,0,0}};
  // --------------------------------------------------------------------
  // INIT WINDOW
  InitWindow(WIDTH, HEIGHT, "dioimperatoresalvini");
  if (!IsWindowReady()) {
    throw std::runtime_error("Unable to initialize window");
  }

  SetTargetFPS(60);
  // --------------------------------------------------------------------
  // REL
  while (!WindowShouldClose()) {
    if(IsKeyPressed(KEY_LEFT)) {
      PAUSED = !PAUSED;
    } else if (!PAUSED) {
      UpdateParticles(a, b);
    }
    BeginDrawing();
    ClearBackground(WHITE);
    //
    DrawParticles(a, b);
    //
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
