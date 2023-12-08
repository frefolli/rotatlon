#ifndef PARSE_PARTICLES_HH
#define PARSE_PARTICLES_HH

#include <rotatlon/particle.hh>
#include <vector>
#include <istream>

void ParseParticles(std::vector<Particle>& out, std::istream& in);

#endif
