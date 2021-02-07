cmake_minimum_required(VERSION 3.7)

project(CHIP8)

set(BIN_DIR ${CHIP8_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CHIP8_SOURCE_DIR}/bin)

include_directories(src)
file(GLOB_RECURSE SRC_FILES
  src/*.cpp
  src/*.hpp
)
include_directories(include)
file(GLOB_RECURSE INC_FILES
  include/*.hpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
add_executable(CHIP8 ${SRC_FILES} ${INC_FILES})

# There is no standard install directory for windows,
# change this to yours!
set(SDL2_MORE_INCLUDE_DIR "C:/sdl2")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARIES})