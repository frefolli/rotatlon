#include <raylib.h>
#include <ctime>
#include <cstring>
#include <random>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <fstream>

#include <rotatlon/config.hh>
#include <rotatlon/particle.hh>
#include <rotatlon/update_particles.hh>
#include <rotatlon/draw_particles.hh>
#include <rotatlon/parse_particles.hh>

bool PAUSED = false;

int realMain(int argc, char** args) {
  // --------------------------------------------------------------------
  // INIT
  std::vector<Particle> particles;
  if (argc < 2) {
    throw std::runtime_error("expected a particle csv FILE path");
  }

  std::ifstream file (args[1]);
  ParseParticles(particles, file);
  file.close();

  if (particles.size() < 1) {
    throw std::runtime_error("no particles fed in " + std::string(args[1]));
  }
  // --------------------------------------------------------------------
  // INIT WINDOW
  InitWindow(WIDTH, HEIGHT, "dioimperatoresalvini");
  if (!IsWindowReady()) {
    throw std::runtime_error("Unable to initialize window");
  }

  SetTargetFPS(TARGET_FPS);
  BeginDrawing();
  ClearBackground(WHITE);
  EndDrawing();
  // --------------------------------------------------------------------
  // REL
  while (!WindowShouldClose()) {
    BeginDrawing();
    DrawParticles(particles);
    if(IsKeyPressed(KEY_LEFT)) {
      PAUSED = !PAUSED;
    } else if (!PAUSED) {
      UpdateParticles(particles);
    }
    EndDrawing();
  }
  // --------------------------------------------------------------------
  // DELETE
  // --------------------------------------------------------------------
  CloseWindow();
  return 0;
}

int main(int argc, char** args) {
  const char* AC_RED = "\u001b[31m";
  const char* AC_RESET = "\u001b[0m";
  try {
    return realMain(argc, args);
  } catch(std::exception& error) {
    std::printf("%sERROR:%s %s\n", AC_RED, AC_RESET, error.what());
    return 1;
  }
}
