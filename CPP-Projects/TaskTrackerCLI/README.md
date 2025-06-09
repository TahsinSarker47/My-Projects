# Task Tracker CLI

A comprehensive command-line task management application built with modern C++ to demonstrate best practices in software architecture, build systems, and project organization.

## Project Structure

Understanding how a well-organized C++ project is structured is crucial for maintainable software development. This project follows industry-standard conventions:

```
TaskTrackerCLI/
├── CMakeLists.txt          # Build system configuration
├── README.md               # Project documentation
├── include/                # Header files (.h)
│   ├── Task.h             # Task class interface
│   └── TaskTracker.h      # TaskTracker class interface
├── src/                   # Implementation files (.cpp)
│   ├── main.cpp           # Application entry point
│   ├── Task.cpp           # Task class implementation  
│   └── TaskTracker.cpp    # TaskTracker class implementation
├── build/                 # Build artifacts (created by CMake)
└── tasks.json            # Data persistence file (created at runtime)
```

## Key Learning Concepts

This project demonstrates several important C++ and software engineering concepts:

### Object-Oriented Design Principles
- **Encapsulation**: Each class has a clear, well-defined interface with implementation details hidden behind private members
- **Separation of Concerns**: The Task class handles individual task data and behavior, while TaskTracker manages collections and persistence
- **Single Responsibility**: Each class has one primary job, making the code easier to understand and maintain

### Modern C++ Features
- **RAII (Resource Acquisition Is Initialization)**: Resources like file handles are automatically managed through constructors and destructors
- **STL Algorithms**: Using `std::find_if`, `std::copy_if`, and `std::max_element` instead of manual loops for more expressive and efficient code
- **Lambda Functions**: Modern C++ closures that make algorithms more readable and powerful
- **Smart Memory Management**: Using containers like `std::vector` that handle memory automatically

### Build System Architecture
- **CMake**: A cross-platform build system that generates native build files for your environment
- **Modular Compilation**: Separating headers from implementation allows for faster compilation and better code organization
- **Configuration Management**: Different build types (Debug/Release) with appropriate compiler flags for development and production

## Building the Project

The build process demonstrates how modern C++ projects are compiled and linked. Here's how to build and run the application:

### Prerequisites
You'll need a C++17-compatible compiler and CMake installed on your system. Most modern systems include these tools:
- **Linux**: `sudo apt install build-essential cmake` (Ubuntu/Debian) or equivalent for your distribution
- **macOS**: Install Xcode command line tools with `xcode-select --install` and CMake with `brew install cmake`
- **Windows**: Install Visual Studio with C++ support and CMake, or use MSYS2/MinGW

### Build Steps

1. **Create the project directory structure**:
   ```bash
   mkdir TaskTrackerCLI
   cd TaskTrackerCLI
   mkdir include src build
   ```

2. **Place the files in their correct locations**:
   - Put `Task.h` and `TaskTracker.h` in the `include/` directory
   - Put `main.cpp`, `Task.cpp`, and `TaskTracker.cpp` in the `src/` directory  
   - Put `CMakeLists.txt` in the root directory

3. **Configure the build system**:
   ```bash
   cd build
   cmake ..
   ```
   
   This step analyzes your system, finds the appropriate compiler, and generates build files. CMake will create Makefiles on Unix systems or Visual Studio project files on Windows.

4. **Compile the project**:
   ```bash
   cmake --build .
   ```
   
   This compiles all source files and links them into the final executable. The build system handles dependencies automatically, so if you modify a header file, all dependent source files will be recompiled.

5. **Run the application**:
   ```bash
   ./task-cli
   ```

## Usage Examples

The command-line interface demonstrates how to design user-friendly CLI applications with clear, consistent commands:

```bash
# Add new tasks
./task-cli add "Learn modern C++ best practices"
./task-cli add "Build a task management system"
./task-cli add "Master CMake build configuration"

# View all tasks
./task-cli list

# Filter tasks by status
./task-cli list todo
./task-cli list in-progress
./task-cli list done

# Update task descriptions
./task-cli update 1 "Learn modern C++ and software architecture"

# Change task status
./task-cli mark-in-progress 1
./task-cli mark-done 2

# Remove completed tasks
./task-cli delete 2
```

## Advanced CMake Features

The CMakeLists.txt file includes several advanced features that demonstrate professional build system management:

### Development Workflow Targets
- `make demo`: Runs a series of commands to demonstrate the application
- `make format`: Automatically formats code using clang-format (if available)
- `make clean-all`: Thoroughly cleans all build artifacts

### Testing Integration
The project includes CTest integration for automated testing:
```bash
cd build
make test
```

### Build Configuration Options
You can build with different optimization levels:
```bash
# Debug build (default) - includes debugging symbols and less optimization
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build - maximum optimization, smaller executable
cmake -DCMAKE_BUILD_TYPE=Release ..
```

## Architecture Deep Dive

Understanding the architectural decisions helps you apply these patterns to other projects:

### File Organization Philosophy
The separation between headers and implementation serves several important purposes:
- **Compilation Speed**: Only implementation files need recompilation when logic changes
- **Interface Stability**: Headers define contracts that remain stable even when implementation evolves
- **Dependency Management**: Clear separation makes it easier to understand what depends on what

### JSON Parsing Strategy
The manual JSON parsing demonstrates string manipulation and parsing techniques. While production applications typically use libraries like nlohmann/json, understanding the underlying principles helps you:
- Debug serialization issues more effectively
- Make informed decisions about when to use libraries versus custom solutions
- Understand the complexity that libraries abstract away

### Error Handling Philosophy
The application demonstrates several error handling strategies:
- **Validation at Boundaries**: Input validation happens immediately when data enters the system
- **Graceful Degradation**: The application continues functioning even when some operations fail
- **User-Friendly Messages**: Error messages guide users toward correct usage rather than showing technical details

## Educational Value

This project serves as a comprehensive example of how to structure a real-world C++ application. The patterns and techniques demonstrated here scale up to much larger systems:

- The modular design makes it easy to add new features without breaking existing functionality
- The build system configuration shows how to manage complex compilation requirements
- The error handling demonstrates how to build robust applications that handle unexpected situations gracefully
- The documentation approach shows how to make code maintainable for other developers

Whether you're learning C++ fundamentals or exploring advanced software architecture concepts, this project provides practical examples of industry-standard practices that you can apply to your own development work.