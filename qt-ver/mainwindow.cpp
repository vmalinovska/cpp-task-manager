#include "helpwindow.h"
#include "mainwindow.h"
#include "taskblock.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Task Manager");

    QWidget *container = new QWidget(); // holds all tasks

    tasksLayout = new QVBoxLayout(container); // sets vertical layout for a list of tasks

    container->setLayout(tasksLayout);

    refreshTasks(); // load saved tasks

    ui->scrollArea->setWidget(container); // container with tasks is in the scroll area
    ui->scrollArea->setWidgetResizable(true);


    tasksLayout->addStretch();
    tasksLayout->setAlignment(Qt::AlignTop);

    ui->addButton->setToolTip("Add a new task");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removeTask(const QUuid& id) {
    manager_.removeTask(id);
    refreshTasks();
}

void MainWindow::refreshTasks()
{
    manager_.sortTasks();
    // delete old taskblocks
    while (QLayoutItem* item = tasksLayout->takeAt(0))
    {
        if (item->widget())
        {
            item->widget()->deleteLater();
        }

        delete item;
    }

    // create new taskblocks
    for (const auto& task : manager_.getTasks())
    {
        TaskBlock* taskblock = new TaskBlock(task);

        connect(taskblock, &TaskBlock::taskChanged, this, &MainWindow::refreshTasks);
        connect(taskblock, &TaskBlock::deleteRequested, this, &MainWindow::removeTask);

        tasksLayout->addWidget(taskblock);
    }
}

void MainWindow::on_addButton_clicked()
{
    QString name = "new task";
    QString descr = "description (optional)";
    auto deadline = std::nullopt;

    std::shared_ptr<Task> task = manager_.addTask(Task(name, descr, deadline));

    TaskBlock *taskblock = new TaskBlock(task);

    connect(taskblock, &TaskBlock::taskChanged, this, &MainWindow::refreshTasks);
    connect(taskblock, &TaskBlock::deleteRequested, this, &MainWindow::removeTask);

    tasksLayout->insertWidget(0, taskblock);

    taskblock->createTask();
}


void MainWindow::on_helpButton_clicked()
{
    HelpWindow hw(this);
    hw.exec();
}

