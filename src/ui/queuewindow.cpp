#include "scheduler.h"
#include "ctexceptions.h"

#include "ui_queuewindow.h"
#include "queuewindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextBrowser>

QueueWindow::QueueWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueueWindow){
    ui->setupUi(this);
}

QueueWindow::~QueueWindow(){
    delete ui;
}

void QueueWindow::setWindow(int maxSteps, Scheduler* sh){
    this->maxSteps = maxSteps;
    if(maxSteps<0) this->maxSteps=this->prevStates.max_size();
    this->scheduler = sh;
    this->init();
}

#define CONNECTBUTTON(x,y) connect(ui->x, SIGNAL(clicked(bool)), this, SLOT(y));
void QueueWindow::init(){
    CONNECTBUTTON(nextButton,nextTick());
    CONNECTBUTTON(lastButton,lastTick());
    CONNECTBUTTON(oldestButton,oldestTick());
    CONNECTBUTTON(previousButton,prevTick());

    ui->previousButton->setEnabled(false);
    ui->oldestButton->setEnabled(false);

    ui->algorithmEdit->setText(QString::fromStdString(scheduler->getAlgorithmName()));

    currentState = scheduler->getState();
}
#undef CONNECTBUTTON

bool QueueWindow::nextTick(){
    try{
        scheduler->nextTick();
        prevStates.push_back(currentState);
        currentState = scheduler->getState();
        if(prevStates.size()>maxSteps) prevStates.pop_front();
        else{
            ui->previousButton->setEnabled(true);
            ui->oldestButton->setEnabled(true);
        }
    }
    catch(ExecutionCompletedException){}
    bool t = this->scheduler->isCompleted();
    if(t){
        ui->nextButton->setEnabled(false);
        ui->lastButton->setEnabled(false);
    }
    updateViews();
    return !t;
}

bool QueueWindow::prevTick(){
    bool q = true;
    if(!prevStates.size()){
        ui->previousButton->setEnabled(false);
        ui->oldestButton->setEnabled(false);
        q = false;
    }
    if(q && prevStates.size()){
        currentState = prevStates.back();
        scheduler->setState(currentState);
        prevStates.pop_back();
        ui->nextButton->setEnabled(true);
        ui->lastButton->setEnabled(true);
    }
    if(!prevStates.size()){
        ui->previousButton->setEnabled(false);
        ui->oldestButton->setEnabled(false);
        q = false;
    }
    updateViews();
    return q;
}

bool QueueWindow::lastTick(){
    while(nextTick());
    return true;
}

bool QueueWindow::oldestTick(){
    while(prevTick());
    return true;
}

void QueueWindow::updateViews(){
    ui->ticksElapsedEdit->setText(QString::fromStdString(
        std::to_string(currentState.ticksElapsed)));

    ui->ticksElapsedEditGC->setText(QString::fromStdString(
        std::to_string(currentState.ticksElapsed)));

    auto rq = currentState.readyQueue;
    std::string id = "-1", name="Nothing", instr="Idle",
                wt="-1", priority="-1";
    if(!rq.empty()){
        id = std::to_string(rq.front()->getPID());
        name = rq.front()->getName();
        auto [d,e] = rq.front()->peek();
        instr = "";
        switch(d){
        case 1:
            instr += "CPU\t"+std::to_string(e)+"\n"; break;
        case 2:
            instr += "IO\t"+std::to_string(e)+"\n"; break;
        case 3:
            instr += "WAIT\t"+std::to_string(e)+"\n"; break;
        case 0:
            if(e==0) instr+="STARTING\n";
            else instr += "DEAD\n";
        default: break;
        }
        wt = std::to_string(rq.front()->getWaitingTime());
        priority = std::to_string(rq.front()->getPriority());
    }

    ui->processIdEdit->setText(QString::fromStdString(id));
    ui->processNameEdit->setText(QString::fromStdString(name));
    ui->instructionEdit->setText(QString::fromStdString(instr));
    ui->instructionEditGC->setText(QString::fromStdString(instr));
    ui->waitingTimeEdit->setText(QString::fromStdString(wt));
    ui->priorityEdit->setText(QString::fromStdString(priority));

    ui->idleTicksEdit->setText(QString::fromStdString(
        std::to_string(currentState.idleTime)));

    ui->idleCyclesEdit->setText(QString::fromStdString(
        std::to_string(currentState.wastedCycles)));

    updateUI();
}

void QueueWindow::updateUI(){
    _updateUI(ui->arrivalQueueEdit,scheduler->arrivalQueue.getQueue());
    _updateUI(ui->readyQueueEdit,scheduler->readyQueue.getQueue());
    _updateUI(ui->waitingQueueEdit,scheduler->waitingQueue.getQueue());
    _updateUI(ui->blockedQueueEdit,scheduler->blockedQueue.getQueue());
    _updateUI(ui->deadQueueEdit,scheduler->deadQueue.getQueue());
    _updateUI(ui->ganttChart,scheduler->ganttChart);
    ui->textLogEdit->insertPlainText(QString::fromStdString(scheduler->logging()));
}

void QueueWindow::_updateUI(QTextBrowser* textEdit, std::vector<Process*> v){
    std::string text;
    for(auto&c:v) text+="  "+std::to_string(c->getPID()) + "  |";
    if(text.size()>2) text.erase(text.size()-2);
    textEdit->setText(QString::fromStdString(text));
}

void QueueWindow::_updateUI(QTextBrowser* textEdit, std::vector<std::pair<int,int>> v){
    std::string text;
    for(auto&c:v) text+="  " + std::to_string(c.second) + " : " + std::to_string(c.first) + "  |";
    if(text.size()>2) text.erase(text.size()-2);
    textEdit->setText(QString::fromStdString(text));
}

