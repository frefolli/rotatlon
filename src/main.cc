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
bool NOX = false;
size_t MAX_ITERATION = 100;

void RaylibSetup() {
  if (!NOX) {
    InitWindow(WIDTH, HEIGHT, "dioimperatoresalvini");
    if (!IsWindowReady()) {
      throw std::runtime_error("Unable to initialize window");
    }

    SetTargetFPS(TARGET_FPS);
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }
}

bool Cycle() {
  static size_t iterations = 0;
  if (!NOX) {
    return !WindowShouldClose();
  }
  iterations++;
  return iterations < MAX_ITERATION;
}

void Update() {
  if (!PAUSED) {
    UpdateParticles(particles);
    DumpParticles(outputFile, particles);
  }
}

void RaylibUpdate() {
  if (!NOX) {
    if(IsKeyPressed(KEY_LEFT)) {
      PAUSED = !PAUSED;
    }
    BeginDrawing();
    DrawParticles(particles);
    EndDrawing();
  }
}

void RaylibTearDown() {
  if (!NOX) {
    CloseWindow();
  }
}

int realMain(int argc, char** args) {
  // --------------------------------------------------------------------
  // INIT
  std::vector<Particle> particles;
  if (argc < 2) {
    throw std::runtime_error("expected an input particle csv FILE path");
  }
  if (argc < 3) {
    throw std::runtime_error("expected an output trace csv FILE path");
  }
  size_t arg_i = 3;
  while (arg_i < argc) {
    std::string flag = args[arg_i];
    if (flag == "-nox") {
      NOX = true;
      arg_i++;
    } else if (flag == "-iter") {
      arg_i++;
      if (!(arg_i < argc)) {
        throw std::runtime_error("-iter expects a number");
      }
      flag = args[arg_i];
      MAX_ITERATION = std::stoi(flag);
      arg_i++;
    } else {
      throw std::runtime_error("unknown argument: " + flag);
    }
  }

  std::ifstream inputFile (args[1]);
  ParseParticles(particles, inputFile);
  inputFile.close();

  if (particles.size() < 1) {
    throw std::runtime_error("no particles fed in " + std::string(args[1]));
  }

  std::ofstream outputFile (args[2]);
  DumpHeader(outputFile);
  // --------------------------------------------------------------------
  // INIT WINDOW
  RaylibSetup();
  // --------------------------------------------------------------------
  // REL
  while(Cycle()) {
    Update();
    RaylibUpdate();
  }
  // --------------------------------------------------------------------
  // DELETE
  // --------------------------------------------------------------------
  outputFile.close();
  RaylibTearDown();
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
