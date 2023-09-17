#ifndef QUEUEWINDOW_H
#define QUEUEWINDOW_H

#include <QMainWindow>

namespace Ui {
class QueueWindow;
}

class QueueWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QueueWindow(QWidget *parent = nullptr);
    ~QueueWindow();

private:
    Ui::QueueWindow *ui;
};

#endif // QUEUEWINDOW_H
