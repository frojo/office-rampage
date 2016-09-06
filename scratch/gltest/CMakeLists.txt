cmake_minimum_required (VERSION 3.6)
project (GLTest)

# Homebrew includes
#include_directories("/usr/local/Cellar/")


find_package(OpenGL REQUIRED)

include_directories("/usr/local/include/")
#include_directories("${PROJECT_BINARY_DIR}")

link_directories("/usr/local/lib/")

#find_library(GLEW_LIB libGLEW.dylib)

file(GLOB SOURCES
	*.cpp
)

add_executable(gltest ${SOURCES})

# Link all da libs I need
target_link_libraries(gltest ${OPENGL_LIBRARIES})
target_link_libraries(gltest libglfw3.dylib)
target_link_libraries(gltest libGLEW.dylib)

