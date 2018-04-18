cmake_minimum_required(VERSION 3.5)
project(pony_td)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_subdirectory("src")
include_directories("src")
include_directories("entityx")

set(ENTITY_X_SOURCES 
    entityx/entityx/System.cc 
    entityx/entityx/Event.cc 
    entityx/entityx/Entity.cc 
    entityx/entityx/help/Timer.cc 
    entityx/entityx/help/Pool.cc
)

add_executable(pony_td ${SOURCES} ${ENTITY_X_SOURCES})

#set_target_properties(pony_td PROPERTIES
#    CXX_STANDARD 14
#    CXX_STANDARD_REQUIRED YES
#    CXX_EXTENSIONS OFF
#)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    message(STATUS ${SFML_INCLUDE_DIR})
    target_link_libraries(pony_td ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# EntityX config
set(ENTITYX_MAJOR_VERSION 1)
set(ENTITYX_MINOR_VERSION 1)
set(ENTITYX_PATCH_VERSION 2)
set(ENTITYX_VERSION ${ENTITYX_MAJOR_VERSION}.${ENTITYX_MINOR_VERSION}.${ENTITYX_PATCH_VERSION})

