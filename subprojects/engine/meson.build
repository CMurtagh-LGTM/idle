project(
  'engine',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++26'],
)

cmake = import('cmake')

raylib_proj_opts = cmake.subproject_options()
raylib_proj_opts.add_cmake_defines({'BUILD_EXAMPLES': 'OFF'})
raylib_proj = cmake.subproject('raylib', options: raylib_proj_opts)
raylib = raylib_proj.dependency('raylib')

imgui_srcs = files('imgui/imgui.cpp', 'imgui/imgui_draw.cpp', 'imgui/imgui_tables.cpp', 'imgui/imgui_widgets.cpp')
imgui_incdir = include_directories('imgui')
imgui = declare_dependency(sources: imgui_srcs, include_directories: imgui_incdir)

rlimgui_srcs = files('rlImGui/rlImGui.cpp')
rlimgui_incdir = include_directories('rlImGui')
rlimgui = declare_dependency(sources: rlimgui_srcs, include_directories: rlimgui_incdir)

subdir('src')
incdir = include_directories('include')

engine_lib = static_library('engine', srcs, imgui_srcs, dependencies: [raylib, imgui], include_directories: incdir)

engine = declare_dependency(link_with: engine_lib)
