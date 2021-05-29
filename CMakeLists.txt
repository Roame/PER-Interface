cmake_minimum_required(VERSION 3.16)

project(Interface VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS "src/*.h")

add_executable(Interface ${SRCS} ${HDRS})

# OpenGL-specific 
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED) 
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_link_libraries(Interface ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})