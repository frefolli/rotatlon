#ifndef DUMP_PARTICLES_HH
#define DUMP_PARTICLES_HH

#include <rotatlon/particle.hh>
#include <ostream>
#include <vector>

void DumpHeader(std::ostream& out);
void DumpParticles(std::ostream& out, std::vector<Particle>& particles);

#endif
