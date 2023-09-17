#include "scheduler.h"

#include "processwindow.h"
#include "ui_processwindow.h"

ProcessWindow::ProcessWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProcessWindow){
    ui->setupUi(this);
}

ProcessWindow::~ProcessWindow(){
    delete ui;
}

void ProcessWindow::setWindow(QString pt, int st, Scheduler* sh){
    this->filePath = pt;
    this->stackSize = st;
    this->scheduler = sh;
}

void ProcessWindow::start(){

}
