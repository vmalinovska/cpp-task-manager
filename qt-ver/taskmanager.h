#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QCoreApplication>
#include <QVector>

#include "task.h"

class TaskManager {
private:
    QVector<std::shared_ptr<Task>> tasks_;

    // returns path to json file with tasks
    static QString getDataPath() {
        return QCoreApplication::applicationDirPath() + "/tasks.json";
    }

    // import tasks from a JSON file
    void loadTasks();

    // save tasks in a JSON file
    void saveTasks();

public:
    // constructor that loads saved tasks
    TaskManager() {
        loadTasks();
    }

    // save all tasks before exiting
    ~TaskManager() {
        saveTasks();
    }

    // sorts tasks
    void sortTasks() {
        std::sort(tasks_.begin(), tasks_.end(), [](const auto& a, const auto& b) {return *a < *b;});
    }

    // adds a new task to and end of the tasks list
    std::shared_ptr<Task> addTask(const Task& task);

    // removes a task with the given id
    void removeTask(const QUuid& task_id);

    [[nodiscard]] const QVector<std::shared_ptr<Task>>& getTasks() const {
        return tasks_;
    }

};

#endif //TASKMANAGER_H
