# CMakeLists.txt - Modern CMake configuration for Task Tracker CLI
# This file demonstrates best practices for C++ project management with CMake

# Specify minimum CMake version - 3.12 provides good modern C++ support
# This ensures we have access to modern CMake features and policies
cmake_minimum_required(VERSION 3.12)

# Define our project with name, version, and language
# The version information can be used throughout the build process
project(TaskTrackerCLI 
    VERSION 1.0.0 
    DESCRIPTION "A command-line task management application written in C++"
    LANGUAGES CXX
)

# Set C++ standard to C++17 - this gives us modern language features
# like structured bindings, filesystem library, and better STL algorithms
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require this standard, don't fall back
set(CMAKE_CXX_EXTENSIONS OFF)        # Use standard C++, not compiler extensions

# Configure build types and compiler flags for better development experience
# These settings help catch bugs early and optimize performance when needed
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)  # Default to Debug for development
endif()

# Set compiler-specific flags for better code quality and debugging
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC and Clang compiler flags
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic -Wshadow -Wconversion")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wall")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Microsoft Visual C++ compiler flags
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /W4 /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG /W4 /MD")
endif()

# Create our executable target by specifying all source files
# This tells CMake to compile these files together into a single program
add_executable(task-cli
    src/main.cpp
    src/Task.cpp
    src/TaskTracker.cpp
)

# Add include directories so the compiler can find our header files
# The PRIVATE keyword means these includes are only for this target
target_include_directories(task-cli PRIVATE
    include
)

# Optional: Add custom targets for common development tasks
# These provide convenient shortcuts for developers

# Custom target to clean all build artifacts
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/task-cli*
    COMMENT "Cleaning all build artifacts"
)

# Custom target to run the application with sample commands
add_custom_target(demo
    COMMAND ./task-cli add "Learn CMake and C++ project structure"
    COMMAND ./task-cli add "Build a task management application"  
    COMMAND ./task-cli add "Practice modern C++ programming"
    COMMAND ./task-cli list
    COMMAND ./task-cli mark-in-progress 1
    COMMAND ./task-cli mark-done 2
    COMMAND ./task-cli list
    DEPENDS task-cli
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running demonstration commands"
)

# Enable testing support - this sets up CTest integration
enable_testing()

# Add a simple test to verify the executable runs without crashing
add_test(NAME help_test 
    COMMAND task-cli
)

# Add a test to verify basic functionality
add_test(NAME basic_functionality_test
    COMMAND ${CMAKE_COMMAND} -E env
    ${CMAKE_BINARY_DIR}/task-cli add "Test task"
)

# Install configuration - useful for distributing the application
# This defines where files should be installed on the system
install(TARGETS task-cli
    RUNTIME DESTINATION bin
    COMPONENT Runtime
)

# Install documentation if README exists
if(EXISTS "${CMAKE_SOURCE_DIR}/README.md")
    install(FILES README.md
        DESTINATION share/doc/task-cli
        COMPONENT Documentation
    )
endif()

# Print configuration summary - helpful for debugging build issues
message(STATUS "=================== Configuration Summary ===================")
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "===========================================================")

# Optional: Support for package managers like Conan or vcpkg
# Uncomment these lines if you're using external dependencies

# find_package(PkgConfig REQUIRED)
# find_package(Threads REQUIRED)

# if(Threads_FOUND)
#     target_link_libraries(task-cli PRIVATE Threads::Threads)
# endif()

# Optional: Add code formatting target using clang-format
find_program(CLANG_FORMAT_EXECUTABLE clang-format)
if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -i
            ${CMAKE_SOURCE_DIR}/src/*.cpp
            ${CMAKE_SOURCE_DIR}/include/*.h
        COMMENT "Formatting source code with clang-format"
    )
endif()

# Optional: Add static analysis target using clang-tidy
find_program(CLANG_TIDY_EXECUTABLE clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    set_target_properties(task-cli PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-checks=*,-fuchsia-*,-google-*,-zircon-*,-abseil-*,-llvm-*"
    )
endif()