#ifndef INFODETAILS_H
#define INFODETAILS_H

#include <QWidget>

namespace Ui {
class InfoDetails;
}

class InfoDetails : public QWidget
{
    Q_OBJECT

public:
    explicit InfoDetails(QWidget *parent = nullptr);
    ~InfoDetails();

private:
    Ui::InfoDetails *ui;
};

#endif // INFODETAILS_H
