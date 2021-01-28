cmake_minimum_required(VERSION 3.16)
project(sanc)

set(SNC_INCLUDE_DIRECTORIES "include" "lib/fmt/include" "lib/range-v3/include" "lib/entt/single-include")
set(SNC_CXX_FLAGS "-Wall")
set(SNC_COMPILE_DEFINITIONS "FMT_HEADER_ONLY")
set(SNC_LINK_LIBRARIES sfml-system sfml-window sfml-graphics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${SNC_CXX_FLAGS})
file(GLOB SNC_SRC "src/math/*.cpp" "src/utility/*.cpp" "src/filesystem/*.cpp" "src/graphics/windowing/*.cpp" "src/graphics/drawing/*.cpp" "src/graphics/interface/*.cpp")

find_package(SFML REQUIRED COMPONENTS graphics window)
add_library(sanc SHARED ${SNC_SRC})

target_include_directories(sanc PRIVATE ${SNC_INCLUDE_DIRECTORIES})
target_compile_definitions(sanc PUBLIC ${SNC_COMPILE_DEFINITIONS})
target_link_libraries(sanc ${SNC_LINK_LIBRARIES})
