cmake_minimum_required(VERSION 3.15...4.0)
project(TaskTrackerCLI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task-cli
    src/main.cpp
    src/Task.cpp
    src/TaskTracker.cpp
)

target_include_directories(task-cli PRIVATE
    include
)