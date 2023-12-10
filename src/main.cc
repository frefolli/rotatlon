#include <raylib.h>
#include <ctime>
#include <cstring>
#include <random>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

#include <rotatlon/config.hh>
#include <rotatlon/particle.hh>
#include <rotatlon/update_particles.hh>
#include <rotatlon/draw_particles.hh>
#include <rotatlon/parse_particles.hh>
#include <rotatlon/dump_particles.hh>
#include <rotatlon/populate_particles.hh>

bool PAUSED = false;
bool NOX = false;
bool RANDOM = false;
size_t MAX_ITERATION = 100;
std::string INPUT_FILE = "input.csv";
std::string OUTPUT_FILE = "output.csv";

void RaylibSetup() {
  if (!NOX) {
  }
}

void NoxWorkflow() {
  std::vector<Particle> particles;
    std::ifstream inputFile (INPUT_FILE);
    ParseParticles(particles, inputFile);
    inputFile.close();
  if (RANDOM) {
    std::srand(std::time(nullptr));
    PopulateParticles(particles);
  }

  size_t iterations = 0;
  std::cout << std::endl;
  
  while(iterations < MAX_ITERATION) {
    iterations++;
    std::cout << "\rRunning iteration " << iterations << " / " << MAX_ITERATION;
    UpdateParticles(particles);
    DumpParticles(outputFile, particles);
  }
  outputFile.close();
}

void XWorkflow() {
  std::vector<Particle> particles;
    std::ifstream inputFile (INPUT_FILE);
    ParseParticles(particles, inputFile);
    inputFile.close();
  if (RANDOM) {
    std::srand(std::time(nullptr));
    PopulateParticles(particles);
  }

  InitWindow(WIDTH, HEIGHT, "dioimperatoresalvini");
  if (!IsWindowReady()) {
    throw std::runtime_error("Unable to initialize window");
  }

  SetTargetFPS(TARGET_FPS);
  BeginDrawing();
  ClearBackground(WHITE);
  EndDrawing();

  #ifdef MODE_3D
  Camera3D camera = { 0 };
  camera.position = (Vector3){ 0.0f, 0.0f, 0.0f };  // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };        // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                              // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;           // Camera mode type
  #else
  Camera2D camera = { 0 };
  camera.target = (Vector2){ 0.0f, 0.0f };
  camera.offset = (Vector2){ WIDTH/2.0f, HEIGHT/2.0f };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  #endif

  while(!WindowShouldClose()) {
    if(IsKeyDown(KEY_LEFT)) {
      WINDOW_SHIFT_X -= 5;
    } else if(IsKeyDown(KEY_UP)) {
      WINDOW_SHIFT_Y -= 5;
    } else if(IsKeyDown(KEY_RIGHT)) {
      WINDOW_SHIFT_X += 5;
    } else if(IsKeyDown(KEY_DOWN)) {
      WINDOW_SHIFT_Y += 5;
    } else if(IsKeyPressed(KEY_P)) {
      PAUSED = !PAUSED;
    } else if(IsKeyPressed(KEY_C)) {
      WINDOW_SHIFT_X = 0;
      WINDOW_SHIFT_Y = 0;
    }
    if (!PAUSED) {
      UpdateParticles(particles);
    }
    BeginDrawing();
    ClearBackground(WHITE);
    #ifdef MODE_3D
      BeginMode3D(camera);
    #else
      BeginMode2D(camera);
    #endif
    DrawParticles(particles);
    #ifdef MODE_3D
      EndMode3D(camera);
    #else
      EndMode2D(camera);
    #endif
    EndDrawing();
  }
  CloseWindow();
}

void readCLI(size_t argc, char** args) {
  size_t arg_i = 1;
  while (arg_i < argc) {
    std::string flag = args[arg_i];
    if (flag == "-nox") {
      NOX = true;
      arg_i++;
    } else if (flag == "-paused") {
      PAUSED = true;
      arg_i++;
    } else if (flag == "-rand") {
      RANDOM = true;
      arg_i++;
    } else  if (flag == "-iter") {
      arg_i++;
      if (!(arg_i < argc)) {
        throw std::runtime_error("-iter expects a number");
      }
      flag = args[arg_i];
      MAX_ITERATION = std::stoi(flag);
      arg_i++;
    } else if (flag == "-delta") {
      arg_i++;
      if (!(arg_i < argc)) {
        throw std::runtime_error("-delta expects a number");
      }
      flag = args[arg_i];
      DTIME = std::stod(flag);
      arg_i++;
    } else if (flag == "-bound") {
      arg_i++;
      if (!(arg_i < argc)) {
        throw std::runtime_error("-bound expects a number");
      }
      flag = args[arg_i];
      BOUNDARY = std::stof(flag);
      arg_i++;
    } else if (flag == "-in") {
      arg_i++;
      if (!(arg_i < argc)) {
        throw std::runtime_error("-in expects a file");
      }
      flag = args[arg_i];
      INPUT_FILE = flag;
      arg_i++;
    } else if (flag == "-out") {
      arg_i++;
      if (!(arg_i < argc)) {
        throw std::runtime_error("-out expects a file");
      }
      flag = args[arg_i];
      OUTPUT_FILE = flag;
      arg_i++;
    } else {
      throw std::runtime_error("unknown argument: " + flag);
    }
  }
}

int main(int argc, char** args) {
  const char* AC_RED = "\u001b[31m";
  const char* AC_RESET = "\u001b[0m";
  try {
    readCLI(argc, args);
    if (NOX) {
      NoxWorkflow();
    } else {
      XWorkflow();
    }
    return 0;
  } catch(std::exception& error) {
    std::printf("%sERROR:%s %s\n", AC_RED, AC_RESET, error.what());
    return 1;
  }
}
