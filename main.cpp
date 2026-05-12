#include <iostream>
#include <nlohmann/detail/abi_macros.hpp>

#include "TaskManager.h"

int main() {
    TaskManager taskManager = TaskManager();
    taskManager.run();
    return 0;
}
