#ifndef QUEUEWINDOW_H
#define QUEUEWINDOW_H

#include "scheduler.h"

#include<queue>
#include<vector>
#include<utility>

#include <QBoxLayout>
#include <QMainWindow>
#include <QWidget>
#include <QTextBrowser>

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
    void updateUI();

private:
    static void _updateUI(QTextBrowser* textEdit,std::vector<Process*>);
    static void _updateUI(QTextBrowser* textEdit,std::vector<std::pair<int,int>>);

    Ui::QueueWindow *ui;
    size_t maxSteps;
    State currentState;
    Scheduler* scheduler;
    std::deque<State> prevStates;
    std::vector<QWidget*> containers;
    std::vector<QHBoxLayout*> layouts;

    void updateViews();
};

#endif // QUEUEWINDOW_H
