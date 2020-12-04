cmake_minimum_required(VERSION 3.17)
project(galaxycmt)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dep/cppast)

find_package(Boost 1.65 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(galaxycmt main.cpp
                         src/walker/walker.h
                         src/walker/dir_walker/dir_walker.h
                         src/walker/dir_walker/dir_walker.cpp)

target_link_libraries(galaxycmt PUBLIC cppast
                                PUBLIC ${Boost_LIBRARIES})