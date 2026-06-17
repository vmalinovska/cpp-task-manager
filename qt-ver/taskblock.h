#ifndef TASKBLOCK_H
#define TASKBLOCK_H

#include "task.h"

#include <QWidget>

namespace Ui {
class TaskBlock;
}

class TaskBlock : public QWidget
{
    Q_OBJECT

public:
    explicit TaskBlock(std::shared_ptr<Task> task, QWidget *parent = nullptr);
    ~TaskBlock();
    void createTask();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_deleteButton_clicked(bool checked);

    void on_completed_toggled(bool checked);

private:
    Ui::TaskBlock *ui;
    std::shared_ptr<Task> task_;

    void beginTitleEdit();
    void finishTitleEdit();

    void beginDescriptionEdit();
    void finishDescriptionEdit();

    void beginDeadlineEdit();
    void finishDeadlineEdit();

signals:
    void deleteRequested(QUuid task_id);
    void taskChanged();
};

#endif // TASKBLOCK_H
