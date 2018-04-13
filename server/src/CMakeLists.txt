cmake_minimum_required(VERSION 3.3.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

project(LewRAT_Server)

include_directories(./ util/ networking/ payload/)

set(SOURCES main.c client.c util/parson.c payload/system.c networking/networking.c)

add_executable(LewRAT_Server ${SOURCES})
target_link_libraries(LewRAT_Server ws2_32)