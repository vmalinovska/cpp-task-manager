#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <QString>
#include <QUuid>
#include <optional>


class Task {
private:
    QString name_;
    QString description_;
    std::optional<QDate> deadline_;
    bool isDone_;
    QUuid id_;

public:
    // constructor of a task
    explicit Task(QString  name, QString  description = "", const std::optional<QDate> deadline = std::nullopt, const bool isDone = false) : name_(name), description_(description), deadline_(deadline), isDone_(isDone), id_(QUuid::createUuid()) {};

    // constructor for loading the task from json
    Task(QString name, QString description, std::optional<QDate> deadline, bool isDone, QUuid id)
        : name_(name)
        , description_(description)
        , deadline_(deadline)
        , isDone_(isDone)
        , id_(id) {};

    // returns a name of the task
    [[nodiscard]] QString getName() const {
        return name_;
    }

    // returns a description of a task
    [[nodiscard]] QString getDescription() const {
        return description_;
    }

    // returns a deadline of a task, even if it's empty
    [[nodiscard]] std::optional<QDate> getDeadline() const {
        return deadline_;
    }

    //returns string version of a deadline
    [[nodiscard]] QString getDeadlineString() const;


    // returns "true" if deadline_ has a value and is not empty
    [[nodiscard]] bool deadlineHasValue() const {
        return deadline_.has_value();
    }

    // returns "true" is the task is done; otherwise returns "false"
    [[nodiscard]] bool isDone() const {
        return isDone_;
    }

    // returns unique id of the task
    [[nodiscard]] QUuid getId() const {
        return id_;
    }

    // sets a new name for an existing task
    void setName(const QString& name) {
        name_ = name;
    }

    // sets a new description for an existing task
    void setDescription(const QString& description) {
        description_ = description;
    }

    // sets a new deadline for an existing task
    void setDeadline(const std::optional<QDate>& deadline) {
        deadline_ = deadline;
    }

    // changes status of a task
    void setIsDone(const bool isDone) {
        isDone_ = isDone;
    }

    // operator of comparison of two tasks
    bool operator==(const Task &other) const {
        return id_==other.id_;
    }

    bool operator<(const Task &other) const;
};

#endif //TASK_H

