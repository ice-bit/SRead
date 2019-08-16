## General options
cmake_minimum_required(VERSION 3.9)
project(sread)

## File globbing
file(GLOB_RECURSE sources sread/src/*.cpp sread/include/*.h)
#file(GLOB_RESOURCE sources_test sread/test*.cpp) # Only for testing

## Target definitions
add_executable(sread ${sources})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_options(sread PUBLIC -std=c++14 -Wall -Wextra -Werror)
target_include_directories(sread PUBLIC sread/src)

## Packages
find_package(Boost 1.69 COMPONENTS program_options REQUIRED)
target_link_libraries(sread PUBLIC
    ${Boost_LIBRARIES}
)

## Testing

## Packaging
install(TARGETS sread DESTINATION sread_destination)
set(CPACK_PACKAGE_NAME "SerialRead")
set(CPACK_PACKAGE_VERSION "0.0.1")
set(CPACK_MONOLITHIC_INSTALL 1)
include(CPack)