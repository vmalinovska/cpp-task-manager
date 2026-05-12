//
// Created by nika mally on 12/05/2026.
//

#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include <ostream>
#include <vector>

#include "Task.h"

class TaskManager {
private:
    std::vector<Task> tasks_;
    static constexpr auto DATA_PATH = "../data/tasks.json";

    // import tasks from a JSON file
    void loadTasks(const std::string& filename);

    // save tasks in a JSON file
    void saveTasks(const std::string& filename);

public:
    // constructor that loads saved tasks
    TaskManager() {
        loadTasks(DATA_PATH);
    }

    // save all tasks before exiting
    ~TaskManager() {
        saveTasks(DATA_PATH);
    }

    // adds a new task to and end of the tasks list
    void addTask(const Task& task) {
        tasks_.push_back(task);
    }

    // removes all tasks from a list of tasks that are equal to given
    void removeTask(const Task& task) {
        tasks_.erase(std::remove(tasks_.begin(), tasks_.end(), task), tasks_.end());
    }

    // prints all the tasks from a list of tasks
    void showAllTasks();

    // shows details of a given task
    void showTask(int idx);

    // main method
    void run();

};

#endif //TASKMANAGER_H
