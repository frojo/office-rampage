cmake_minimum_required (VERSION 3.6)
project (GLTest)

# Homebrew includes
#include_directories("/usr/local/Cellar/")


find_package(OpenGL REQUIRED)

include_directories("/usr/local/include/")
include_directories("gainput-0.10.0-beta/lib/include")
#include_directories("${PROJECT_BINARY_DIR}")

link_directories("/usr/local/lib/")
link_directories("gainput-0.10.0-beta/build/lib")

#find_library(GLEW_LIB libGLEW.dylib)

file(GLOB SOURCES
	*.cpp
)

add_executable(exec ${SOURCES})

# Link all da libs I need
target_link_libraries(exec ${OPENGL_LIBRARIES})
target_link_libraries(exec libglfw3.dylib)
target_link_libraries(exec libGLEW.dylib)
target_link_libraries(exec libgainput.dylib)
