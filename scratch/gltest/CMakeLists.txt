cmake_minimum_required (VERSION 3.6)
project (GLTest)

# Homebrew includes
include_directories("/usr/local/Cellar/")


include_directories("/usr/local/include/")
include_directories("${PROJECT_BINARY_DIR}")

link_directories("/usr/local/lib/")

add_executable(gltest gltest.cpp)
target_link_libraries(gltest libglfw3.dylib)


