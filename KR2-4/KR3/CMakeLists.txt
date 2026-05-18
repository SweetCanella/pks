cmake_minimum_required(VERSION 3.10)

project(elevator_sim
    VERSION 0.1.0
    DESCRIPTION "Симулятор работы лифтов в здании"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(Threads REQUIRED)

set(ELEVATOR_SIM_SOURCES
    src/main.cpp
    src/simulation.cpp
    src/dispatcher.cpp
    src/elevator.cpp
    src/statistics.cpp
    src/nearest_elevator_strategy.cpp
    src/min_queue_strategy.cpp
    src/strategy_factory.cpp)

add_executable(elevator_sim ${ELEVATOR_SIM_SOURCES})

target_include_directories(elevator_sim
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(elevator_sim
    PRIVATE
        Threads::Threads)

if(MSVC)
    target_compile_options(elevator_sim PRIVATE /W4 /permissive-)
else()
    target_compile_options(elevator_sim PRIVATE -Wall -Wextra -Wpedantic)
endif()
