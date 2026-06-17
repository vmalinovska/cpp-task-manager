#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "taskmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_addButton_clicked();
    void removeTask(const QUuid& id);
    void refreshTasks();

    void on_helpButton_clicked();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *tasksLayout;
    TaskManager manager_;
};
#endif //
