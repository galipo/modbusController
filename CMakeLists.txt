cmake_minimum_required(VERSION 3.6)
project(modbuspp)
set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES modbus_controller.cpp)

include_directories(./)

add_executable(modbus ${SOURCE_FILES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


target_link_libraries(modbus Threads::Threads)