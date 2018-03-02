cmake_minimum_required(VERSION 2.8.3)
project(pony_td)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_executable(pony_td src/main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(pony_td ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
