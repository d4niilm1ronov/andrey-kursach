#ifndef DETAILSDISPLAY_H
#define DETAILSDISPLAY_H

#include <QDialog>

namespace Ui {
class detailsdisplay;
}

class detailsdisplay : public QDialog
{
    Q_OBJECT

public:
    explicit detailsdisplay(QWidget *parent = nullptr);
    ~detailsdisplay();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_search2_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_reset_2_clicked();

private:
    Ui::detailsdisplay *ui;
};

#endif // DETAILSDISPLAY_H
