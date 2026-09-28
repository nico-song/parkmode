cmake_minimum_required(VERSION 3.20)
project(parkmode CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5)
FetchContent_MakeAvailable(raylib)

find_package(Threads REQUIRED)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)
add_executable(parkmode ${SRC})
target_include_directories(parkmode PRIVATE include)
target_link_libraries(parkmode PRIVATE raylib Threads::Threads)
target_compile_definitions(parkmode PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")
