#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BOARD.hide();
    INFODETAILS.hide();
    ui->gridLayout_game->addWidget(&BOARD, 0, 0);
    ui->gridLayout_game->addWidget(&INFODETAILS, 0, 1);
    BOARD.setMinimumSize(QSize(500, 700));
    BOARD.setMaximumSize(QSize(500, 700));
    BOARD.show();
    INFODETAILS.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    INFODETAILS.setMinimumWidth(353);
    INFODETAILS.setMaximumWidth(353);
    INFODETAILS.show();
}

MainWindow::~MainWindow()
{
    qDebug()<<"delete main"<<Qt::endl;
    delete &BOARD;
    delete &INFODETAILS;
    delete ui;
}

