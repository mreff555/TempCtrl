cmake_minimum_required(VERSION 3.11)
project(TempCtrl VERSION 0.0.1 
  DESCRIPTION "Multi-Purpose Temperature Controller"
    LANGUAGES CXX)
add_compile_options(-Wall -Wextra -W -Wshadow -Wformat -fexceptions)
set(CMAKE_CXX_FLAGS_DEBUG "-g -pipe")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -pipe")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("src" "test")
file(GLOB SOURCES "src/*.cpp")

### Unit Testing ###
enable_testing()

#file(GLOB TEST_SOURCES "test/*.cpp")

macro(add_unit_test TARGET_TEST)
  string(REPLACE "_test" "" CLASS_DEFINITION ${TARGET_TEST})
    add_test(${TARGET_TEST} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_TEST})
    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${TARGET_TEST})
    add_executable(
      ${TARGET_TEST}
      test/${TARGET_TEST}.cpp
      src/${CLASS_DEFINITION}.cpp
      )
    target_link_libraries(${TARGET_TEST} GTest::gtest_main)
endmacro(add_unit_test)

include(FetchContent)
FetchContent_Declare(
  wiringpi
  GIT_REPOSITORY https://github.com/WiringPi/WiringPi
  GIT_TAG 2.61-1
  )
FetchContent_MakeAvailable(wiringpi)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
  )
FetchContent_MakeAvailable(googletest)
include_directories(${googletest_SOURCE_DIR}/googletest/include/gtest)

add_unit_test(bitfield_test)
add_unit_test(button_test)
# add_unit_test(buttonManager_test)       #Button class dependancy
# add_unit_test(buttonSubscriber_test)    #Button class dependancy
add_unit_test(common_test)
# add_unit_test(dataManager_test)         #WiringPi dependancy
# add_unit_test(lcdScreen_test)           #WiringPi dependancy
# add_unit_test(pidProcessor_test)i       #???
# add_unit_test(pwmController_test)       #WiringPi dependancy
add_unit_test(thermocoupleReceiver_test)

# TODO: Need to Set up mocks and add additional arguments to macro
# to handle dependancies.  Also need to finish all unit tests

include(GoogleTest)
gtest_discover_tests(common_test)
# TODO Need to run tests on build and fail if tests do not pass
# reference this: https://stackoverflow.com/questions/15115075/how-to-run-ctest-after-building-my-project-with-cmake

#TODO: WiringPi won't build on Apple because dependancies won't compile
# (I forget the dep name), Need an if check for operating system type

# FetchContent_Declare(
#   wiringpi
#   GIT_REPOSITORY https://github.com/WiringPi/WiringPi
#   GIT_TAG 2.61-1
#   )
# FetchContent_MakeAvailable(wiringpi)
# include_directories(${wiringpi_SOURCE_DIR}/wiringPi)

# add_executable(
#   ${CMAKE_PROJECT_NAME}
#   ${SOURCES}
#   )
# 
# target_link_libraries(
#   ${CMAKE_PROJECT_NAME}
#   wiringpi
#   )

