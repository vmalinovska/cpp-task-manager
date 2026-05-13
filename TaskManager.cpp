//
// Created by nika mally on 12/05/2026.
//

#include "TaskManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void TaskManager::loadTasks(const std::string& filename) {
    std::ifstream file(filename);

    // open file
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
    }

    // do not do anything if there were no tasks
    if (file.peek() == std::ifstream::traits_type::eof()) {

        std::ofstream out(filename);
        out << "[]";

        return;
    }

    // read json
    json j = json::parse(file);

    std::string name;
    std::string description;
    bool isDone;

    // write tasks to task manager
    for (const auto& jtask : j) {

        jtask.at("name").get_to(name);
        jtask.at("description").get_to(description);
        std::optional<Date> deadline = std::nullopt;
        jtask.at("isDone").get_to(isDone);

        // check if the deadline is initialized
        if (!jtask["deadline"].is_null()) {

            std::string jdeadline;
            jtask.at("deadline").get_to(jdeadline);

            int day, month, year;
            char separator;

            std::istringstream inputstr(jdeadline);
            inputstr >> day >> separator >> month >> separator >> year;

            deadline = Date(day, month, year);
        }

        tasks_.emplace_back(name, description, deadline, isDone); // emplace creates a new object in a vector, this allows us to skip an unnecessary copy
    }
}

void TaskManager::saveTasks(const std::string &filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
    }

    // we will write our tasks here
    json j = json::array();

    for (const auto& task : tasks_) {
        json jtask;

        jtask["name"] = task.getName();
        jtask["description"] = task.getDescription();

        if (task.deadlineHasValue()) {
            jtask["deadline"] = task.getDeadline(); // string version of Date object
        } else {
            jtask["deadline"] = nullptr; // nlohmann/json.hpp interprets nullptr as a null
        }
        jtask["isDone"] = task.isDone();

        j.push_back(jtask);
    }

    file << j.dump(4);
}

void TaskManager::showMainMenu() const {
    std::cout << "Current task count: " << tasks_.size() << std::endl;
    std::cout << "TASKS LIST: " << std::endl;

    if (tasks_.empty()) {
        std::cout << "Nothing here..." << std::endl;
    } else {
        for (int i=0; i<tasks_.size(); i++) {
            std::cout << i+1 << ". " << tasks_.at(i).getName() << std::endl;
        }
    }

    showOptions();
}

void TaskManager::showTaskMenu(const int idx) {
    showTask(idx);

    std::cout << std::endl << "CHOOSE OPTION: " << std::endl;

    std::cout << "1. MENU - see all of the tasks" << std::endl;
    std::cout << "2. EDIT - edit current task" << std::endl;
    std::cout << "3. DELETE - remove this task" << std::endl;
    std::cout << "4. EXIT - save the changes and exit the task manager" << std::endl;

    std::string option;
    std::getline(std::cin, option);

    if (option == "MENU") {
        showMainMenu();
    } else if (option == "DELETE") {
        this->removeTask(idx);
        std::cout << std::endl << "TASK DELETED" << std::endl;
        showMainMenu();
    } else if (option == "EDIT") {
        std::string name;
        std::string description;
        std::string duedate;
        std::string completed;

        std::cout << "NAME: ";
        std::getline(std::cin, name);
        tasks_.at(idx).setName(name);

        std::cout << "DESCRIPTION (optional): ";
        std::getline(std::cin, description);
        tasks_.at(idx).setDescription(description);

        std::cout << "DUE DATE (optional): ";
        std::getline(std::cin, duedate);

        std::cout << "COMPLETED (yes/no): ";
        std::getline(std::cin, completed);

        std::optional<Date> deadline = std::nullopt;
        if (!duedate.empty()) {
            int d, m ,y;

            std::istringstream inputstr(duedate);
            inputstr >> d >> m >> y;
            deadline = Date(d, m, y);
        }
        tasks_.at(idx).setDeadline(deadline);

        if (completed == "yes") {
            tasks_.at(idx).setIsDone(true);
        } else {
            if (completed != "no")
                std::cout << "Unknown command. Setting task as uncompleted..." << std::endl;
            tasks_.at(idx).setIsDone(false);
        }
        showMainMenu();
    } else if (option == "EXIT") {
        stop();
    }
}

void TaskManager::showOptions() {
    std::cout << std::endl << "CHOOSE OPTION: " << std::endl;

    std::cout << "1. VIEW_ALL - see all of the tasks" << std::endl;
    std::cout << "2. VIEW [n] - see the task nr. n" << std::endl;
    std::cout << "3. ADD - add a new task" << std::endl;
    std::cout << "4. REMOVE [n] - remove a task nr. n" << std::endl;
    std::cout << "5. EXIT - save the changes and exit the task manager" << std::endl;
}

void TaskManager::showAllTasks() {
    if (tasks_.empty()) {
        std::cout << "Nothing here..." << std::endl;
        return;
    }
    for (const auto& task : tasks_) {
        std::cout << task.toString() << std::endl;
    }
}

void TaskManager::showTask(int idx) {
    std::cout << tasks_.at(idx).toString() << std::endl;
}

void TaskManager::run() {
    showMainMenu();

    while (running) {
        std::string option;

        std::getline(std::cin, option);

        if (option == "VIEW_ALL") {
            showAllTasks();
            showOptions();
        } else if (option.starts_with("VIEW ")) {
            int idx = std::stoi(option.substr(5));
            idx--;

            if (idx < 0 || idx >= tasks_.size()) {
                std::cout << "Invalid index" << std::endl;
                continue;
            }

            showTaskMenu(idx);

        } else if (option == "ADD") {
            std::string name;
            std::string description;
            std::string duedate;

            std::cout << "NAME: ";
            std::getline(std::cin, name);

            std::cout << "DESCRIPTION (optional): ";
            std::getline(std::cin, description);

            std::cout << "DUE DATE (optional): ";
            std::getline(std::cin, duedate);

            std::optional<Date> deadline = std::nullopt;
            if (!duedate.empty()) {
                int d, m ,y;

                std::istringstream inputstr(duedate);
                inputstr >> d >> m >> y;
                deadline = Date(d, m, y);
            }

            addTask(Task(name, description, deadline));
            std::cout << std::endl << "TASK ADDED" << std::endl;
            showMainMenu();

        } else if (option.starts_with("REMOVE ")) {
            int idx = std::stoi(option.substr(5));
            idx--;

            if (idx < 0 || idx >= tasks_.size()) {
                std::cout << "Invalid index" << std::endl;
                continue;
            }

            this->removeTask(idx);
            std::cout << std::endl << "TASK REMOVED" << std::endl;
            showMainMenu();

        } else if (option == "EXIT") {
            std::cout << "Bye!" << std::endl;
            stop();

        } else {
            std::cout << "Invalid option" << std::endl;
        }
    }

}

