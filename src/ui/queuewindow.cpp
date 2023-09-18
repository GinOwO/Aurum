#include "scheduler.h"
#include "ctexceptions.h"

#include "ui_queuewindow.h"
#include "queuewindow.h"

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

void QueueWindow::init(){
    connect(ui->nextButton, SIGNAL(clicked(bool)), this, SLOT(nextTick()));
    connect(ui->lastButton, SIGNAL(clicked(bool)), this, SLOT(lastTick()));
    connect(ui->oldestButton, SIGNAL(clicked(bool)), this, SLOT(oldestTick()));
    connect(ui->previousButton, SIGNAL(clicked(bool)), this, SLOT(prevTick()));

    ui->previousButton->setEnabled(false);
    ui->oldestButton->setEnabled(false);

    ui->ganttChart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->algorithmEdit->setText(QString::fromStdString(scheduler->getAlgorithmName()));

    currentState = scheduler->getState();
}

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

    auto rq = currentState.readyQueue;
    std::string id = "-1", name="Nothing", instr="Idle",
        bt="-1", wt="-1", priority="-1";
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
        bt = std::to_string(scheduler->processTable.getProcess(rq.front()->getPID())->getBurstTime());
        wt = std::to_string(rq.front()->getWaitingTime());
        priority = std::to_string(rq.front()->getPriority());
    }

    ui->processIdEdit->setText(QString::fromStdString(id));
    ui->processNameEdit->setText(QString::fromStdString(name));
    ui->instructionEdit->setText(QString::fromStdString(instr));
    ui->burstTimeEdit->setText(QString::fromStdString(bt));
    ui->waitingTimeEdit->setText(QString::fromStdString(wt));
    ui->priorityEdit->setText(QString::fromStdString(priority));

    ui->idleTicksEdit->setText(QString::fromStdString(
        std::to_string(currentState.idleTime)));

    ui->idleCyclesEdit->setText(QString::fromStdString(
        std::to_string(currentState.wastedCycles)));
}
