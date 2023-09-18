#ifndef QUEUEWINDOW_H
#define QUEUEWINDOW_H

#include "scheduler.h"

#include<queue>

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class QueueWindow;
}

class QueueWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit QueueWindow(QWidget *parent = nullptr);
    ~QueueWindow();
    void setWindow(int, Scheduler*);
    void init();

private slots:
    bool nextTick();
    bool lastTick();
    bool prevTick();
    bool oldestTick();

private:
    Ui::QueueWindow *ui;
    size_t maxSteps;
    State currentState;
    Scheduler* scheduler;
    std::deque<State> prevStates;

    void updateViews();
};

#endif // QUEUEWINDOW_H
