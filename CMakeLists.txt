cmake_minimum_required(VERSION 3.10.2)

project(tempctrl
DESCRIPTION "PID Temperature controller"
LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Remove for compiler-specific features
set(CMAKE_CXX_EXTENSIONS OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall")
string(APPEND CMAKE_CXX_FLAGS " -Wbuiltin-macro-redefined")
string(APPEND CMAKE_CXX_FLAGS " -pedantic")
# string(APPEND CMAKE_CXX_FLAGS " -Werror")
string(APPEND CMAKE_CXX_FLAGS " -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow")
string(APPEND CMAKE_CXX_FLAGS " -Wformat")
string(APPEND CMAKE_CXX_FLAGS " -fexceptions")

# clangd completion
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(wiringPi REQUIRED)

include_directories(
#    ${WIRINGPI_INCLUDE_DIRS}
    src)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries((${PROJECT_NAME} ${WIRINGPI_LIBRARIES}))
# Link against wiringPi
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIBRARIES})

