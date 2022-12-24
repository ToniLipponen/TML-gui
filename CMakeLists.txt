cmake_minimum_required(VERSION 3.10)
project(tml-gui)

add_subdirectory(TML)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(tml-gui ${TML_LIBRARY_TYPE} ${SRC_FILES})
target_link_libraries(tml-gui tml-graphics tml-window tml-system)
