#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "scheduler.h"

#include "processwindow.h"
#include "queuewindow.h"

#include <QDialog>
#include <QString>

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
    void setWindow(ProcessWindow*, Scheduler*, QueueWindow*);

private slots:
    void on_buttonBox_accepted();
    void on_browse_clicked();

private:
    Ui::StartWindow *ui;
    ProcessWindow* processWindow;
    Scheduler* scheduler;
    QueueWindow* queueWindow;
};

#endif // STARTWINDOW_H
