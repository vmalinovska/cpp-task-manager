//
// Created by nika mally on 12/05/2026.
//

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>

#include "Task.h"

class TaskManager {
private:
    std::vector<Task> tasks_;
    static constexpr auto DATA_PATH = "../data/tasks.json";
    bool running = true;

    // import tasks from a JSON file
    void loadTasks(const std::string& filename);

    // save tasks in a JSON file
    void saveTasks(const std::string& filename);

    // shows main menu with names of the tasks
    void showMainMenu() const;

    // shows details of a chosen task and options of what user can do with this task
    void showTaskMenu(int idx);

    // shows options like view all, delete, etc.
    static void showOptions();

public:
    // constructor that loads saved tasks
    TaskManager() {
        loadTasks(DATA_PATH);
    }

    // save all tasks before exiting
    ~TaskManager() {
        saveTasks(DATA_PATH);
    }

    void stop() {
        running = false;
    }

    // adds a new task to and end of the tasks list
    void addTask(const Task& task) {
        tasks_.push_back(task);
    }

    // removes all tasks from a list of tasks that are equal to given
    void removeTask(int idx) {
        tasks_.erase(tasks_.begin() + idx);
    }

    // prints all the tasks from a list of tasks
    void showAllTasks();

    // shows details of a given task
    void showTask(int idx);

    // main method
    void run();

};

#endif //TASKMANAGER_H
