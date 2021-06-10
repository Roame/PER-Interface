cmake_minimum_required(VERSION 3.16)

project(Interface VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HDRS CONFIGURE_DEPENDS "src/*.h")

add_executable(Interface ${SRCS} ${HDRS})