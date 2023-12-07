project('rotatlon', 'cpp', version: 'master')

include = include_directories('include')

main = executable('main.exe', [
    'src/particle.cc',
    'src/v3.cc',
    'src/v2.cc',
    'src/main.cc',
  ], 
  dependencies: dependency('raylib'),
  include_directories : include)
