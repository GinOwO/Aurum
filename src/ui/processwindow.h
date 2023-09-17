#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H

#include "scheduler.h"

#include <QMainWindow>
#include <QString>

namespace Ui {
class ProcessWindow;
}

class ProcessWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ProcessWindow(QWidget *parent = nullptr);
    ~ProcessWindow();
    void setWindow(QString, int, Scheduler*);
    void start();

private:
    Ui::ProcessWindow *ui;
    Scheduler* scheduler;
    QString filePath;
    int stackSize;
};

#endif // PROCESSWINDOW_H
