#include "task.h"
#include <QString>

QString Task::getDeadlineString() const {
    if (deadline_.has_value()) {
        return deadline_->toString("dd MMM yyyy");
    }
    return "ASAP";
}

bool Task::operator<(const Task &other) const {

    // undone tasks have to be at the top of the list
    if (isDone_ < other.isDone_) {
        return true;

    // comparing two tasks with the same "completed" state
    } else if (isDone_ == other.isDone_) {

        // if a task dedaline set to ASAP then it wins
        if (!deadline_.has_value())
            return other.deadline_.has_value(); // this wins if other has deadline, otherways it loses

        if (!other.deadline_.has_value())
            return false;


        // if both tasks are undone, we sort them by deadline - the closer to today's day wins
        QDate today = QDate::currentDate();
        int this_day_diff = std::abs(deadline_->daysTo(today));
        int other_day_diff = std::abs(other.deadline_->daysTo(today));
        return this_day_diff < other_day_diff;
    }
    return false;
}


