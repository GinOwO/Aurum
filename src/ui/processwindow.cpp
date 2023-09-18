#include "scheduler.h"

#include "processwindow.h"
#include "ui_processwindow.h"

#include<string>
#include<QString>

ProcessWindow::ProcessWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProcessWindow){
    ui->setupUi(this);
}

ProcessWindow::~ProcessWindow(){
    delete ui;
}

void ProcessWindow::setWindow(QString pt, Scheduler* sh){
    this->filePath = pt;
    this->scheduler = sh;
    this->init();
}

void ProcessWindow::init(){
    scheduler->load(filePath.toStdString());
    this->processList = scheduler->processTable.listProcesses();
    sort(processList.begin(), processList.end());
    ui->comboBox->insertItem(0,QString("Select a process"));
    for(auto&c:processList){
        auto P = scheduler->processTable.getProcess(c);
        std::string s = std::to_string(c) + " : " + P->getName();
        ui->comboBox->insertItem(c,QString::fromStdString(s));
    }
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_process_select()));
}

void ProcessWindow::on_process_select(){
    int idx = this->ui->comboBox->currentIndex();
    if(idx>0){
        auto t = scheduler->processTable.viewProcess(processList[idx-1]);
        ui->textBrowser->setText(QString::fromStdString(t));
    }
    else ui->textBrowser->setText(QString("Select a process"));

}
