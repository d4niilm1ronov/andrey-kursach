#ifndef USERREG_H
#define USERREG_H
#include <QDialog>

namespace Ui {
class userreg;
}

class userreg : public QDialog
{
    Q_OBJECT

public:
    explicit userreg(QWidget *parent = nullptr);
    ~userreg();

private slots:
   // void on_pushButton_reg_clicked();

    void on_pushButton_reg_clicked();

private:
    Ui::userreg *ui;

};

#endif // USERREG_H
