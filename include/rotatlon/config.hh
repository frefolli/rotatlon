#ifndef CONFIG_HH
#define CONFIG_HH
//#define MODE_3D

#include <cstddef>
#include <string>

extern double BOUNDARY;
extern double DTIME;

extern size_t WIDTH;
extern size_t HEIGHT;
extern size_t TARGET_FPS;
extern bool PAUSED;
extern bool NOX;
extern bool RANDOM;
extern size_t MAX_ITERATION;
extern std::string INPUT_FILE;
extern std::string OUTPUT_FILE;

#endif
