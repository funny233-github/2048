cmake_minimum_required(VERSION 3.20.2)

project(2048)

find_package(Curses REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(${PROJECT_SOURCE_DIR})


file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set(CURSES_NEED_NCURSES TRUE)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
