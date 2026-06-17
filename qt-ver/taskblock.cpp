#include "task.h"
#include "taskblock.h"
#include "ui_taskblock.h"

TaskBlock::TaskBlock(std::shared_ptr<Task> task, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TaskBlock)
    , task_(task)
{
    ui->setupUi(this);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // width can change, height cannot changes
    ui->taskDescription->setWordWrap(true);
    ui->taskTitle->setWordWrap(true);
    setAttribute(Qt::WA_StyledBackground, true);
    ui->deleteButton->setAttribute(Qt::WA_Hover, true);

    ui->taskTitle->setText(task->getName());
    ui->taskDescription->setText(task->getDescription());
    ui->taskDeadline->setText(task->getDeadlineString());
    ui->completed->setChecked(task->isDone());

    ui->deleteButton->installEventFilter(this);

    // EDITING FIELDS

    // title
    ui->taskTitle->installEventFilter(this);
    connect(ui->titleEdit_, &QLineEdit::editingFinished, this, &TaskBlock::finishTitleEdit);

    ui->stackedTitle->setCurrentIndex(0);

    // description
    ui->taskDescription->installEventFilter(this);
    ui->descriptionEdit_->installEventFilter(this);

    ui->stackedDescription->setCurrentIndex(0);

    // date
    ui->taskDeadline->installEventFilter(this);
    connect(ui->dateEdit_, &QDateEdit::dateChanged, this, &TaskBlock::finishDeadlineEdit);

    ui->stackedDate->setCurrentIndex(0);

    ui->completed->setToolTip("Mark task as completed");
    ui->stackedTitle->setToolTip("Double-click to edit a task title");
    ui->stackedDescription->setToolTip("Double-click to edit a task description");
    ui->deleteButton->setToolTip("Delete task");
    ui->stackedDate->setToolTip("Double-click to edit a deadline. Anything sooner \nthan current date will be marked as ASAP");
}

TaskBlock::~TaskBlock()
{
    delete ui;
}

bool TaskBlock::eventFilter(QObject *obj, QEvent *event) {

    if (obj == ui->deleteButton) {

        if (event->type() == QEvent::Enter) {
            ui->deleteButton->setIcon(QIcon(":/icons/trash-red.svg"));

        } else if (event->type() == QEvent::Leave) {
            ui->deleteButton->setIcon(QIcon(":/icons/trash.svg"));
        }
    }

    if (obj == ui->taskTitle && event->type() == QEvent::MouseButtonDblClick) {
        beginTitleEdit();
        return true; // event is "resolved", do not send it to the function that called this function
    }

    if (obj == ui->taskDescription && event->type() == QEvent::MouseButtonDblClick) {
        beginDescriptionEdit();
        return true; // event is "resolved", do not send it to the function that called this function
    }

    if (obj == ui->descriptionEdit_ && event->type() == QEvent::FocusOut) {
        finishDescriptionEdit();
        return true; // event is "resolved", do not send it to the function that called this function
    }

    if (obj == ui->taskDeadline && event->type() == QEvent::MouseButtonDblClick) {
        beginDeadlineEdit();
        return true;
    }

    return QWidget::eventFilter(obj, event);
}

// DELETE BUTTON
void TaskBlock::on_deleteButton_clicked(bool checked) {
    emit deleteRequested(task_->getId());
}

// COMPLETED
void TaskBlock::on_completed_toggled(bool checked) {
    task_->setIsDone(checked);
    emit taskChanged();
}

// TITLE
void TaskBlock::beginTitleEdit() {

    ui->titleEdit_->setText(ui->taskTitle->text());

    ui->stackedTitle->setCurrentIndex(1);

    ui -> titleEdit_->setFocus();

}

void TaskBlock::finishTitleEdit() {
    QString newTitle = ui->titleEdit_->text();

    task_->setName(newTitle);

    ui->taskTitle->setText(newTitle);

    ui->titleEdit_->clear();

    ui->stackedTitle->setCurrentIndex(0);
}

// DESCRIPTION
void TaskBlock::beginDescriptionEdit() {

    ui->descriptionEdit_->setPlainText(ui->taskDescription->text());

    ui->stackedDescription->setCurrentIndex(1);

    ui -> descriptionEdit_->setFocus();

}

void TaskBlock::finishDescriptionEdit() {
    QString newDescr = ui->descriptionEdit_->toPlainText();

    task_->setDescription(newDescr);

    ui->taskDescription->setText(newDescr);

    ui->descriptionEdit_->clear();

    ui->stackedDescription->setCurrentIndex(0);

}

// DEADLINE
void TaskBlock::beginDeadlineEdit() {
    auto curDeadline = task_->getDeadline();

    if (curDeadline.has_value())
        ui->dateEdit_->setDate(*curDeadline);
    else
        ui->dateEdit_->setDate(QDate::currentDate());

    ui->dateEdit_->setDisplayFormat("dd.MM.yyyy");
    ui->dateEdit_->setCalendarPopup(true);

    ui->stackedDate->setCurrentIndex(1);
    ui->dateEdit_->setFocus();
}

void TaskBlock::finishDeadlineEdit() {
    auto newDeadline = ui->dateEdit_->date();

    if (newDeadline < QDate::currentDate()) {
        task_->setDeadline(std::nullopt);
    } else {
        task_->setDeadline(newDeadline);
    }
    ui->taskDeadline->setText(task_->getDeadlineString());
    ui->stackedDate->setCurrentIndex(0);
}

// CREATING NEW TASK
void TaskBlock::createTask() {
    beginTitleEdit();
}



