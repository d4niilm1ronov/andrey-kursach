#ifndef SELLDETAILS_H
#define SELLDETAILS_H

#include <QDialog>

namespace Ui {
class selldetails;
}

class selldetails : public QDialog
{
    Q_OBJECT

public:
    explicit selldetails(QWidget *parent = nullptr);
    ~selldetails();

private slots:
    void on_pushButton_back_clicked();

    void on_lineEdit_drugid_returnPressed();

    void on_lineEdit_drugid_editingFinished();

    void on_pushButton_clicked();

    void on_pushButton_pressed();

    void on_pushButton_add_clicked();

    void on_pushButton_refresh_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_totalamnt_clicked();

    void on_pushButton_saveinfo_clicked();

    void on_pushButton_print_clicked();
    bool queryToCsv();

private:
    Ui::selldetails *ui;
};

#endif // SELLDETAILS_H
