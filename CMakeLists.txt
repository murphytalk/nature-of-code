cmake_minimum_required(VERSION 3.5)
project(CMakeSFMLProject LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /Zc:__cplusplus")
    add_compile_definitions(NOMINMAX)
else(MSVC)
    set (CMAKE_CXX_STANDARD 20)
endif(MSVC)

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

FetchContent_Declare(cli11
    URL https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.4.2.tar.gz
)
FetchContent_MakeAvailable(cli11)
include_directories(${cli11_SOURCE_DIR}/include)

FetchContent_Declare(raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(raylib-cpp
    URL https://github.com/RobLoach/raylib-cpp/archive/refs/tags/v5.0.0.tar.gz
)
FetchContent_MakeAvailable(raylib-cpp)
include_directories(${raylib-cpp_SOURCE_DIR}/include)

include(CMake/internal_utils.cmake)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(play)
add_subdirectory(nature-of-code)
