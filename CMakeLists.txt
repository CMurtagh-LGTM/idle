cmake_minimum_required(VERSION 4.3.2)

project(
	idle
	VERSION 0.0.1
	LANGUAGES CXX
)

# Make sure all binaries are placed into the same build folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)
FetchContent_Declare(engine SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine)
FetchContent_MakeAvailable(engine)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(${PROJECT_NAME} engine)
