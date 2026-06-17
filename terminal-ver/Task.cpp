//
// Created by nika mally on 12/05/2026.
//

#include "Task.h"
#include <sstream>

std::string Task::getDeadline() const {
    if (deadline_.has_value()) {
        return deadline_->toString(); // other way: deadline_.value().toString() - we have to get the true object out of "optional" object before using class methods
    }
    return "ASAP";
}

std::string Task::toString() const {
    std::stringstream answ;
    answ << "Name: " << name_ << std::endl;
    if (!description_.empty()) {
        answ << "Description: " << description_ << std::endl;
    }
    answ << "Deadline: " << (deadline_.has_value() ? deadline_->toString() : "ASAP") << std::endl;
    answ << "Completed: " << (isDone_ ? "yes" : "no") << std::endl;

    return answ.str();
}

Task& Task::operator=(const Task &other) {
    if (this == &other) {
        return *this;
    }

    name_ = other.name_;
    description_ = other.description_;
    deadline_ = other.deadline_;
    isDone_ = other.isDone_;
    return *this;
}

