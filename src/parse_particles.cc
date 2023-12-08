#include <cstdio>
#include <cstring>
#include <rotatlon/parse_particles.hh>
#include <stdexcept>
#include <string>
#include <raylib.h>
#include <iostream>

const int HEX_COLOR_SIZE = 9;

unsigned char hex_as_int (char c) {
  if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  } else if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  } else if (c >= '0' && c <= '9') {
    return c - '0';
  } else {
    throw std::runtime_error("invalid hex char '" + std::string(1, c) + "'");
  }
}

inline unsigned char hex2_as_int (char higher, char lower) {
  return 16 * hex_as_int(higher) + hex_as_int(lower);
}

Color detect_color(char* color) {
  static_assert(9 == HEX_COLOR_SIZE, "Update hex color parsing");
  if (strlen(color) != HEX_COLOR_SIZE || color[0] != '#') {
    throw std::runtime_error("invalid color read '" + std::string(color) + "'");
  }

  return {
    hex2_as_int(color[1], color[2]),
    hex2_as_int(color[3], color[4]),
    hex2_as_int(color[5], color[6]),
    hex2_as_int(color[7], color[8]),
  };
}

void ParseParticles(std::vector<Particle>& out, std::istream& in) {
  std::string line;
  size_t index_of_line = 0;
  while (std::getline(in, line)) {
    index_of_line++;
    float mass, px, py, pz, sx, sy, sz;
    int radius;
    char color[HEX_COLOR_SIZE + 1]; // #RRGGBBAA

    if (! (sscanf(line.c_str(), ("%f,%f,%f,%f,%f,%f,%f,%d,%" + std::to_string(HEX_COLOR_SIZE) + "s").c_str(), &mass, &px, &py, &pz, &sx, &sy, &sz, &radius, color) == 9)) {
      throw std::runtime_error("at line " + std::to_string(index_of_line) + ", invalid particle csv: " + line);
    }
    
    Particle particle = {
      mass,
      {px, py, pz},
      {sx, sy, sz},
      radius,
      detect_color(color)
    };

    out.push_back(particle);
    std::cout << particle << std::endl;
  }
}
