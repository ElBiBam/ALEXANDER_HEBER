#include "mainwindow.h"

#include <QApplication>
//#include "mylibrary/singleton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Singleton<MainWindow> s;
    MainWindow w;
    w.show();
    return a.exec();
}
