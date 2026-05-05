cmake_minimum_required(VERSION 4.3.2)

project(
	engine
	VERSION 0.0.1
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
	set(EMSCRIPTEN TRUE)
endif()

option(LINT_ENGINE "Run clang-tidy" OFF)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME}
	PRIVATE
	src/engine.cpp
	src/utils.cpp

	src/layout/text.cpp
	src/layout/image.cpp
	src/layout/vertical_box.cpp
	src/layout/panel.cpp
	src/layout/root.cpp

	src/context.cpp
	src/sprite_manager.cpp
	src/text_manager.cpp
	src/shape_manager.cpp
	src/transform_manager.cpp
)
target_sources(${PROJECT_NAME}
	INTERFACE
	include/engine/engine.hpp

	include/engine/utils/utils.hpp
	include/engine/utils/settings_tuple.hpp
	include/engine/utils/type_traits.hpp

	include/engine/component/sprite.hpp
	include/engine/component/shape.hpp
	include/engine/component/text.hpp
	include/engine/component/transform.hpp
	include/engine/component/text_settings.hpp
	include/engine/component/shape_settings.hpp

	include/engine/layout/text.hpp
	include/engine/layout/image.hpp
	include/engine/layout/vertical_box.hpp
	include/engine/layout/panel.hpp
	include/engine/layout/controls.hpp
	include/engine/layout/root.hpp
	
	include/internal/arena.hpp
	include/internal/config.hpp
	include/internal/context.hpp
	include/internal/manager.hpp
	include/internal/managed_ptr.hpp
	include/internal/sprite_manager.hpp
	include/internal/text_manager.hpp
	include/internal/shape_manager.hpp
	include/internal/transform_manager.hpp

	include/internal/layout/control_pointer.hpp
)
target_compile_definitions(${PROJECT_NAME} PUBLIC LOG)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

if (LINT_ENGINE)
	find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
	set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "--warnings-as-errors=-*")
	set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif ()

set(CF_FRAMEWORK_BUILD_SAMPLES OFF)
set(CF_FRAMEWORK_BUILD_TESTS OFF)
set(CF_RUNTIME_SHADER_COMPILATION OFF)
set(CF_CUTE_SHADERC OFF)

include(FetchContent)

FetchContent_Declare(
	cute
	GIT_REPOSITORY https://github.com/RandyGaul/cute_framework
	GIT_TAG master
	GIT_SHALLOW ON
)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.2.1"
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(cute GSL)

include(ExternalProject)
find_program(MESON meson REQUIRED)
ExternalProject_Add(
	sigc++
	GIT_REPOSITORY https://github.com/libsigcplusplus/libsigcplusplus.git
	GIT_TAG "3.8.0"
	GIT_SHALLOW ON

	SOURCE_DIR     ${CMAKE_BINARY_DIR}/_deps/sigc++-src
	BINARY_DIR     ${CMAKE_BINARY_DIR}/_deps/sigc++-build
	INSTALL_DIR    ${CMAKE_BINARY_DIR}/_deps/sigc++-install

	STEP_TARGETS   install

	UPDATE_COMMAND ""

	CONFIGURE_COMMAND ${MESON} setup <BINARY_DIR> <SOURCE_DIR> 
                      --default-library=static 
                      -Dbuildtype=release 
                      --prefix <INSTALL_DIR>
		      -Dmaintainer-mode=false
		      -Dbuild-deprecated-api=false
		      -Dbuild-examples=false
		      -Dbuild-tests=false
	CONFIGURE_HANDLED_BY_BUILD ON

	BUILD_COMMAND ${MESON} compile -C <BINARY_DIR>
	BUILD_BYPRODUCTS <BINARY_DIR>/sigc++/libsigc-3.0.a

	INSTALL_COMMAND ${MESON} install -C <BINARY_DIR>
	INSTALL_BYPRODUCTS <INSTALL_DIR>/lib/libsigc-3.0.a
)
add_dependencies(${PROJECT_NAME} sigc++-install)
add_library(libsigc++ STATIC IMPORTED)
make_directory(${CMAKE_BINARY_DIR}/_deps/sigc++-install/include/sigc++-3.0)
make_directory(${CMAKE_BINARY_DIR}/_deps/sigc++-install/lib/sigc++-3.0/include)
set_target_properties(libsigc++ PROPERTIES
	IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/_deps/sigc++-install/lib/libsigc-3.0.a
	INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR}/_deps/sigc++-install/include/sigc++-3.0;${CMAKE_BINARY_DIR}/_deps/sigc++-install/lib/sigc++-3.0/include"
)


target_link_libraries(${PROJECT_NAME} PUBLIC cute)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC $<TARGET_PROPERTY:cute,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(${PROJECT_NAME} PUBLIC libsigc++)
target_link_libraries(${PROJECT_NAME} PUBLIC Microsoft.GSL::GSL)
