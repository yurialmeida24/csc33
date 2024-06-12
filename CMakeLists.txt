cmake_minimum_required(VERSION 3.10)

project(Lab3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(fibonacci_multithread fibonacci_multithread.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(fibonacci_multithread PRIVATE Threads::Threads)
