cmake_minimum_required(VERSION 3.10)

project(part2)

add_executable(main
    src/main.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE Threads::Threads)