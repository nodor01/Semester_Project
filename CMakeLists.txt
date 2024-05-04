cmake_minimum_required(VERSION 3.27)
project(Semester_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(Semester_Project main.cpp)

set(SFML_DIR "C:\\SFML\\lib\\cmake\\SFML")

target_link_libraries(Semester_Project sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.6 REQUIRED graphics network audio window system)

