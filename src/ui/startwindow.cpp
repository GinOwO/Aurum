#include "scheduler.h"
#include "schalg.h"

#include "startwindow.h"
#include "ui_startwindow.h"
#include "processwindow.h"
#include "queuewindow.h"
#include <QFileDialog>
#include <QString>

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow){
    ui->setupUi(this);

    for(auto&[a,b]:availableAlgorithmsMap){
        ui->dropDownBox->insertItem(a,QString::fromStdString(b));
    }
}

StartWindow::~StartWindow(){
    delete ui;
}

void StartWindow::on_buttonBox_accepted(){
    QString filePath = ui->textEdit->toPlainText();
    int maxSteps = ui->textEdit_3->toPlainText().toInt();
    QString algo = ui->dropDownBox->currentText();

    processWindow->setWindow(filePath, scheduler);
    scheduler->selectAlgorithm(algo.toStdString());
    processWindow->show();

    queueWindow->setWindow(maxSteps, scheduler);
    queueWindow->show();

    accept();
}

void StartWindow::on_browse_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Select a File", QDir::homePath(), "All Files (*.*)");
    ui->textEdit->setPlainText(path);
}

void StartWindow::setWindow(ProcessWindow* mw, Scheduler* sh, QueueWindow* qw){
    this->processWindow = mw;
    this->scheduler = sh;
    this->queueWindow = qw;
}
