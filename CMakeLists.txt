cmake_minimum_required(VERSION 3.16)
project(sanctuary)
add_subdirectory(lib/sanclib)

set(SNC_INCLUDE_DIRECTORIES "include" "lib/sanclib/include" "lib/sanclib/lib/range-v3/include")
set(SNC_CXX_FLAGS "-Wall")
set(SNC_LINK_LIBRARIES sfml-system sfml-window sfml-graphics sanc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${SNC_CXX_FLAGS})
file(GLOB SNC_SRC "src/*.cpp")

find_package(SFML REQUIRED COMPONENTS graphics window)
add_executable(sanctuary ${SNC_SRC})
target_include_directories(sanctuary PRIVATE ${SNC_INCLUDE_DIRECTORIES})
target_link_libraries(sanctuary ${SNC_LINK_LIBRARIES})
