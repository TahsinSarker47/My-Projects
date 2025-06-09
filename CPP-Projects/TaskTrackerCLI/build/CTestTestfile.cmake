# CMake generated Testfile for 
# Source directory: /run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker
# Build directory: /run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(help_test "/run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/build/task-cli")
set_tests_properties(help_test PROPERTIES  _BACKTRACE_TRIPLES "/run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/CMakeLists.txt;84;add_test;/run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/CMakeLists.txt;0;")
add_test(basic_functionality_test "/usr/bin/cmake" "-E" "env" "/run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/build/task-cli" "add" "Test task")
set_tests_properties(basic_functionality_test PROPERTIES  _BACKTRACE_TRIPLES "/run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/CMakeLists.txt;89;add_test;/run/media/tahsin/New Volume1/Programming/Languages/C++/Projects/Task Tracker/CMakeLists.txt;0;")
