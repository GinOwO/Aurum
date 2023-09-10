#include <QApplication>
#include "src/mainwindow.h" // Include your main window header

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create and show the main window
    MainWindow mainWindow;
    mainWindow.show();

    // Start the main event loop
    return app.exec();
}
