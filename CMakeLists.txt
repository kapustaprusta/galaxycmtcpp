cmake_minimum_required(VERSION 3.17)
project(galaxycmt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.65 COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set (HEADERS src/parser/parser.h
             src/parser/ast_parser/ast_parser.h)

set (SOURCES main.cpp
             src/parser/ast_parser/ast_parser.cpp)

add_executable(galaxycmt ${HEADERS}
                         ${SOURCES})

target_link_libraries(galaxycmt PUBLIC ${Boost_LIBRARIES})