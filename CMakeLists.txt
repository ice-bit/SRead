### General settings
cmake_minimum_required(VERSION 3.9)
project(SRead)


### File globbing
file(GLOB_RECURSE sources src/main/*.cpp src/serial_read/*.cpp src/serial_read/*.h)
file(GLOB_RECURSE sources_test src/test/*.cpp)

### Target definitions
add_executable(sread ${sources})
# CMake compiler flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Compiler flags
target_compile_options(sread PUBLIC -std=c++14 -Wall -Wextra -Werror)
# Inclue headers with angle brackets(<>) instead of " "
target_include_directories(sread PUBLIC src/main src/serial_read)
# Retrieve Boost libraries
find_package(Boost 1.69 COMPONENTS program_options REQUIRED)
# Target libraries
target_link_libraries(sread PUBLIC
    ${Boost_LIBRARIES}
)

### Testing
# Find google test framework
find_package(GTest)

if(GTEST_FOUND)
    add_executable(unit_tests ${sources_test} ${sources})
    target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)
    set_target_properties(sread PROPERTIES ENABLE_EXPORTS ON)

    target_link_libraries(unit_tests PUBLIC
        ${GTEST_BOTH_LIBRARIES}
        sread
    )

    target_include_directories(unit_tests PUBLIC
        ${GTEST_INCLUDE_DIRS}
    )
endif()


### Packaging
install(TARGETS sread DESTINATION SRead_destination)
set(CPACK_PACKAGE_NAME "SRead")
set(CPACK_PACKAGE_VERSION "0.0.3")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)