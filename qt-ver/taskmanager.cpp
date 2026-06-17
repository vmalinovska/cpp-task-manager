#include "taskmanager.h"
#include <iostream>
#include <fstream>
#include <QString>
#include <QDate>

#include <json.hpp>

using json = nlohmann::json;

std::shared_ptr<Task> TaskManager::addTask(const Task& task) {
    auto t = std::make_shared<Task>(task);
    tasks_.push_back(t);
    // sortTasks();
    return t;
}

void TaskManager::removeTask(const QUuid& task_id) {
    for (int i=0; i<tasks_.size(); i+=1) {
        if (tasks_[i]->getId() == task_id) {
            tasks_.erase(tasks_.begin() + i);
            break;
        }
    }
    // sortTasks();
}

void TaskManager::loadTasks() {
    std::ifstream file(getDataPath().toStdString());

    // open file
    if (!file.is_open()) {
        std::cerr << "Error opening file " << getDataPath().toStdString() << std::endl;
        return;
    }

    // do not do anything if there were no tasks
    if (file.peek() == std::ifstream::traits_type::eof()) {

        std::ofstream out(getDataPath().toStdString());
        out << "[]";

        return;
    }

    // read json
    json j = json::parse(file);

    QString name;
    QString description;
    bool isDone;

    // write tasks to task manager
    for (const auto& jtask : j) {

        name = QString::fromStdString(jtask["name"]);
        description = QString::fromStdString(jtask["description"]);
        std::optional<QDate> deadline = std::nullopt;
        isDone = jtask["isDone"];

        // check if the deadline is initialized
        if (!jtask["deadline"].is_null()) {

            QString jdeadline = QString::fromStdString(jtask["deadline"]);

            deadline = QDate::fromString(jdeadline, Qt::ISODate);
        }
        QUuid id = QUuid(QString::fromStdString(jtask["id"]));

        tasks_.emplace_back(std::make_shared<Task>(name, description, deadline, isDone, id)); // emplace creates a new object in a vector, this allows us to skip an unnecessary copy
    }

    // sort tasks after loading, std::sort in the method sortTasks() uses overloaded operator< defined and implemented in tasks.cpp
    // sortTasks();
}

void TaskManager::saveTasks() {
    std::ofstream file(getDataPath().toStdString());

    if (!file.is_open()) {
        std::cerr << "Error opening file " << getDataPath().toStdString() << std::endl;
    }

    // we will write our tasks here
    json j = json::array();

    for (const auto& task : std::as_const(tasks_)) {
        json jtask;

        jtask["name"] = task->getName().toStdString();
        jtask["description"] = task->getDescription().toStdString();

        if (task->deadlineHasValue()) {
            jtask["deadline"] = task->getDeadline()->toString(Qt::ISODate).toStdString(); // string version of Date object
        } else {
            jtask["deadline"] = nullptr; // nlohmann/json.hpp interprets nullptr as a null
        }
        jtask["isDone"] = task->isDone();
        jtask["id"] = task->getId().toString().toStdString();

        j.push_back(jtask);
    }

    file << j.dump(4);
}




