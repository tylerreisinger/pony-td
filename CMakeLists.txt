cmake_minimum_required(VERSION 2.8.3)
project(pony_td)

add_executable(pony_td src/main.cpp)

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(pony_td ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
