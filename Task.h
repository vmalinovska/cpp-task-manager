//
// Created by nika mally on 12/05/2026.
//

#ifndef TASK_H
#define TASK_H

#include <string>

#include "Date.h"

class Task {
private:
    std::string name_;
    std::string description_;
    std::optional<Date> deadline_;
    bool isDone_;

public:
    // constructor of a task
    explicit Task(std::string  name, std::string  description = "", const std::optional<Date> deadline = std::nullopt, const bool isDone = false) : name_(std::move(name)), description_(std::move(description)), deadline_(deadline), isDone_(isDone) {};

    // returns a name of the task
    [[nodiscard]] std::string getName() const {
        return name_;
    }

    // returns a description of a task
    [[nodiscard]] std::string getDescription() const {
        return description_;
    }

    // returns a deadline of a task, or "ASAP" if the task has to be done as soon as possible
    [[nodiscard]] std::string getDeadline() const;

    // returns "true" if deadline_ has a value and is not empty
    [[nodiscard]] bool deadlineHasValue() const {
        return deadline_.has_value();
    }

    // returns "true" is the task is done; otherwise returns "false"
    [[nodiscard]] bool isDone() const {
        return isDone_;
    }

    // sets a new name for an existing task
    void setName(std::string  name) {
        name_ = std::move(name);
    }

    // sets a new description for an existing task
    void setDescription(std::string  description) {
        description_ = std::move(description);
    }

    // sets a new deadline for an existing task
    void setDeadline(std::optional<Date> deadline) {
        deadline_ = deadline;
    }

    // changes status of a task
    void setIsDone(const bool isDone) {
        isDone_ = isDone;
    }

    // returns task full description: name, description, deadline, completed status
    [[nodiscard]] std::string toString() const;

    // operator of comparison of two tasks
    bool operator==(const Task &other) const {
        return name_ == other.name_ && description_ == other.description_ && deadline_ == other.deadline_ && isDone_ == other.isDone_;
    }
};

#endif //TASK_H
