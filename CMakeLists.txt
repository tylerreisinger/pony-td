cmake_minimum_required(VERSION 3.5)
project(pony_td)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_subdirectory("src")

add_executable(pony_td ${SOURCES})

set_target_properties(pony_td PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS OFF
)

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(pony_td ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
