cmake_minimum_required(VERSION 3.20.2)

project(Project2048 VERSION 1.0)

find_package(Curses REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})


file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)

file(GLOB CONFIGURE_FILE
    "${PROJECT_SOURCE_DIR}/lib_configure"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

configure_file("${CONFIGURE_FILE}/mainConfigure.h.in" mainConfigure.h)

set(CURSES_NEED_NCURSES TRUE)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
