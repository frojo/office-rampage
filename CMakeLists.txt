cmake_minimum_required (VERSION 3.6)
project (Office-Rampage)

find_package(OpenGL REQUIRED)

# Find our shader files
configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.hpp.in"
	"${PROJECT_SOURCE_DIR}/src/config.hpp"
	)

# Grabs all source files
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS 
	${PROJECT_SOURCE_DIR}/src/*.h 
	#	${PROJECT_SOURCE_DIR}/third-party/*.h 
	${PROJECT_SOURCE_DIR}/src/*.hpp)
	#${PROJECT_SOURCE_DIR}/third-party/*.hpp)

set (INCLUDE_DIRS "")
foreach  (_headerfile ${HEADERS})
	get_filename_component(_dir ${_headerfile} PATH)
	list (APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS})

include_directories("/usr/local/include/")
include_directories("third-party/gainput/lib/include")
#include_directories("gainput-0.10.0-beta/lib/include")
#include_directories("${PROJECT_BINARY_DIR}")

link_directories("/usr/local/lib/")
link_directories("third-party/gainput/build/lib")

#find_library(GLEW_LIB libGLEW.dylib)


add_executable(exec ${SOURCES})

# Link all da libs I need
target_link_libraries(exec ${OPENGL_LIBRARIES})
target_link_libraries(exec libglfw3.dylib)
target_link_libraries(exec libGLEW.dylib)
target_link_libraries(exec libgainput.dylib)
