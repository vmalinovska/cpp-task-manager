cmake_minimum_required(VERSION 3.29)
project(cpp_task_manager)

find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_task_manager main.cpp
        Date.cpp
        Date.h
        Task.cpp
        Task.h
        TaskManager.cpp
        TaskManager.h
)
target_link_libraries(cpp_task_manager PRIVATE nlohmann_json::nlohmann_json)