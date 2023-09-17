#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "scheduler.h"

#include "processwindow.h"

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
    void setWindow(ProcessWindow*, Scheduler*);

private slots:
    void on_buttonBox_accepted();
    void on_browse_clicked();

private:
    Ui::StartWindow *ui;
    ProcessWindow* processWindow;
    Scheduler* scheduler;
};

#endif // STARTWINDOW_H
