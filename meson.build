project(
  'idle',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++26', 'default_library=static'],
)

engine_proj = subproject('engine')
engine = engine_proj.get_variable('engine')

subdir('src')
incdir = include_directories('include')

idle = executable('idle', srcs, dependencies: [engine], include_directories: incdir)
