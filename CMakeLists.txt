cmake_minimum_required( VERSION 2.8 )
project(task_neon_learning)
set(demo_name  test_task)

add_definitions("-Wall -g")
set(CMAKE_BUILD_TYPE Release)
include_directories(${PROJECT_SOURCE_DIR}/Task1)

set(__ARM_NEON OFF CACHE BOOL "USE ARM NEON")
if(__ARM_NEON)
   add_definitions(-D__ARM_NEON)
   message(STATUS "__ARM_NEON====>:${__ARM_NEON}")
endif()

add_executable(${demo_name} ./Task1/task1.cpp)
