cmake_minimum_required(VERSION 3.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main Board.cpp)
target_link_libraries(main ${CURSES_LIBRARIES})
