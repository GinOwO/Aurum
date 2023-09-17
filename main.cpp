#include "scheduler.h"

#include "src/ui/startwindow.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    ProcessWindow processWindow;
    Scheduler scheduler(100,1);

    StartWindow startWindow;
    startWindow.setWindow(&processWindow,&scheduler);
    startWindow.show();

    return app.exec();
}
