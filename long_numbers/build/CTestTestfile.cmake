# CMake generated Testfile for 
# Source directory: /home/dima/Documents/MPM/homework-for-modern-programming-methods-/long_numbers
# Build directory: /home/dima/Documents/MPM/homework-for-modern-programming-methods-/long_numbers/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(LongNumberTests "/home/dima/Documents/MPM/homework-for-modern-programming-methods-/long_numbers/build/long_numbers_tests")
set_tests_properties(LongNumberTests PROPERTIES  _BACKTRACE_TRIPLES "/home/dima/Documents/MPM/homework-for-modern-programming-methods-/long_numbers/CMakeLists.txt;21;add_test;/home/dima/Documents/MPM/homework-for-modern-programming-methods-/long_numbers/CMakeLists.txt;0;")
subdirs("googletest/googletest")
