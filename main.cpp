#include "scheduler.h"

#include "src/ui/startwindow.h"
#include "src/ui/processwindow.h"
#include "src/ui/queuewindow.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    ProcessWindow processWindow;
    QueueWindow queueWindow;
    Scheduler scheduler(100,1);

    StartWindow startWindow;
    startWindow.setWindow(&processWindow,&scheduler,&queueWindow);
    startWindow.show();

    return app.exec();
}
