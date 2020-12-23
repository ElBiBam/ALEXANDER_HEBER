#include "infodetails.h"
#include "ui_infodetails.h"

InfoDetails::InfoDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoDetails)
{
    ui->setupUi(this);
}

InfoDetails::~InfoDetails()
{
    delete ui;
}
