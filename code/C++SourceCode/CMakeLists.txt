cmake_minimum_required(VERSION 2.8)
set(PRJ_NAME hridancedemo001)
project(${PRJ_NAME} )


# -----------------------------  ARIA  -----------------
include_directories(/usr/local/Aria/include)
link_directories(/usr/local/Aria/lib)
set(LIBS_ARIA Aria ArNetworking rt dl pthread)

add_executable(${PRJ_NAME} Hridd.cpp PioneerRobot.cpp PortDevice.cpp Zxtar.cpp main.cpp)
target_link_libraries(${PRJ_NAME} ${LIBS_ARIA})
