cmake_minimum_required(VERSION 3.17)
project(galaxycmt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.65 COMPONENTS log        REQUIRED
                                   filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set (HEADERS src/parser/parser.h
             src/walker/walker.h
             src/utils/logger/logger.h
             src/parser/ast_parser/ast_parser.h
             src/walker/dir_walker/dir_walker.h)

set (SOURCES main.cpp
             src/utils/logger/logger.cpp
             src/parser/ast_parser/ast_parser.cpp
             src/walker/dir_walker/dir_walker.cpp)

add_executable(galaxycmt ${HEADERS}
                         ${SOURCES})

add_definitions(-DBOOST_LOG_DYN_LINK)

target_link_libraries(galaxycmt PUBLIC pthread
                                PUBLIC ${Boost_LIBRARIES})