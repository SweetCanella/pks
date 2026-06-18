cmake_minimum_required(VERSION 3.16)

project(elevator_sim
    VERSION 1.0.0
    DESCRIPTION "Console elevator simulation with tests and Docker packaging"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CORE_SOURCES
    src/simulation.cpp
    src/dispatcher.cpp
    src/elevator.cpp
    src/statistics.cpp
    src/nearest_elevator_strategy.cpp
    src/min_queue_strategy.cpp
    src/strategy_factory.cpp)

add_library(elevator_core STATIC ${CORE_SOURCES})
target_include_directories(elevator_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
    target_compile_options(elevator_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(elevator_core PRIVATE -Wall -Wextra -Wpedantic)
endif()


add_executable(elevator_sim src/main.cpp)
target_link_libraries(elevator_sim PRIVATE elevator_core)

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/tests/third_party")

enable_testing()

set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_request.cpp
    tests/test_simple_queue.cpp
    tests/test_nearest_strategy.cpp
    tests/test_min_queue_strategy.cpp
    tests/test_strategy_factory.cpp
    tests/test_statistics.cpp
    tests/test_elevator.cpp
    tests/test_dispatcher.cpp)

add_executable(unit_tests ${TEST_SOURCES})
target_include_directories(unit_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tests")
target_link_libraries(unit_tests PRIVATE elevator_core Catch2)

add_test(NAME unit_tests COMMAND unit_tests)

set(SCENARIOS
    scenario_single_elevator
    scenario_nearest_dispatch
    scenario_min_queue_balance
    scenario_full_simulation)

foreach(scenario ${SCENARIOS})
    add_executable(${scenario} "tests/scenarios/${scenario}.cpp")
    target_link_libraries(${scenario} PRIVATE elevator_core)
endforeach()
