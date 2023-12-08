project('rotatlon', 'cpp', version: 'master')

include = include_directories('include')

main = executable('main.exe', [
    'src/config.cc',
    'src/particle.cc',
    'src/v3.cc',
    'src/v2.cc',
    'src/update_particles.cc',
    'src/draw_particles.cc',
    'src/parse_particles.cc',
    'src/dump_particles.cc',
    'src/populate_particles.cc',
    'src/main.cc',
  ], 
  dependencies: dependency('raylib'),
  include_directories : include)
