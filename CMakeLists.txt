cmake_minimum_required(VERSION 3.28)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif ()

set(PROJECT_OUTPUT_BIN_DIR "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_OUTPUT_BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_OUTPUT_BIN_DIR}")

include_directories(vendor/SFML/include)

set(SFML_USE_STATIC_STD_LIBS TRUE)
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(vendor/SFML)

file(GLOB_RECURSE PONG_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${PONG_SOURCES})

add_executable(${PROJECT_NAME} ${PONG_SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window)
