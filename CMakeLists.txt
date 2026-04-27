cmake_minimum_required(VERSION 4.3.2)

project(
	idle
	VERSION 0.0.1
	LANGUAGES CXX
)

# Make sure all binaries are placed into the same build folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)
FetchContent_Declare(engine SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine)
FetchContent_MakeAvailable(engine)

add_executable(
    ${PROJECT_NAME}
)
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(${PROJECT_NAME} engine)

find_program(CLANG_FORMAT_EXE clang-format)
get_target_property(format_sources ${PROJECT_NAME} SOURCES)
# get_target_property(format_interface_sources ${PROJECT_NAME} INTERFACE_SOURCES)
get_target_property(format_engine_sources engine SOURCES)
get_target_property(format_engine_interface_sources engine INTERFACE_SOURCES)
list(TRANSFORM format_engine_sources PREPEND engine/)
add_custom_target(check-format
    COMMENT "Checking files with clang-format..." 
    COMMAND ${CLANG_FORMAT_EXE} --dry-run ${format_sources} ${format_interface_sources} ${format_engine_sources} ${format_engine_interface_sources}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
) 
add_custom_target(format
    COMMENT "Formatting files with clang-format..." 
    COMMAND ${CLANG_FORMAT_EXE} -i ${format_sources} ${format_interface_sources} ${format_engine_sources} ${format_engine_interface_sources}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
) 
