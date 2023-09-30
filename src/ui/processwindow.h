#ifndef PROCESSWINDOW_H
#define PROCESSWINDOW_H

#include "scheduler.h"

#include <vector>
#include <string>

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
    void setWindow(QString, Scheduler*);
    void init();

private slots:
    void on_process_select();

private:
    Ui::ProcessWindow *ui;
    std::vector<std::string> processList;
    Scheduler* scheduler;
    QString filePath;
};

#endif // PROCESSWINDOW_H
