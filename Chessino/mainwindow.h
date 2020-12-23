#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mylibrary/mylibrary_global.h"
#include "mylibrary/share_typedef.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MYLIBRARYSHARED_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
