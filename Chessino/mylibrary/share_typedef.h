#ifndef SHARE_TYPEDEF_H
#define SHARE_TYPEDEF_H

#include "singleton.h"
#include "mainwindow.h"
#include "board.h"
#include "infodetails.h"

#define MAINWINDOW SINGLETON(MainWindow)
#define BOARD SINGLETON(Board)
#define INFODETAILS SINGLETON(InfoDetails)

#endif // SHARE_TYPEDEF_H
