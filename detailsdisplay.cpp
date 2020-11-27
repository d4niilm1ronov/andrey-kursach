#include "detailsdisplay.h"
#include "ui_detailsdisplay.h"
#include "dashboard.h"
#include "stocks.h"
#include <QDebug>
#include<QMessageBox>
detailsdisplay::detailsdisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailsdisplay)
{
    ui->setupUi(this);
}

detailsdisplay::~detailsdisplay()
{
    delete ui;
}

void detailsdisplay::on_pushButton_clicked()
{
    hide();
    Dashboard s;
    s.setModal(true);
    s.exec();
}

void detailsdisplay::on_pushButton_4_clicked()
{
    Stocks s;
    QSqlQueryModel *m = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery *qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_salerecord");
    qry->exec();
    m->setQuery(*qry);
    ui->tableView_2->setModel(m);
    s.connClose();
    qDebug() <<( m->rowCount());

}

void detailsdisplay::on_pushButton_2_clicked()
{
    Stocks s;
    QSqlQueryModel *m = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery *qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_sellcomplete");
    qry->exec();
    m->setQuery(*qry);
    ui->tableView->setModel(m);
    s.connClose();
    qDebug() <<( m->rowCount());

}

void detailsdisplay::on_pushButton_search_clicked()
{
    Stocks s;
    QString srch= ui->lineEdit_search->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery* qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_sellcomplete where bill_no like'%"+srch+"%' or customer_name like'%"+srch+"%'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
     s.connClose();
     qDebug()<<( modal->rowCount());

}

void detailsdisplay::on_pushButton_search2_clicked()
{
    Stocks s;
    QString srch= ui->lineEdit_search2->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery* qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_salerecord where bill_no like'%"+srch+"%' or id like'%"+srch+"%' or dname like'%"+srch+"%'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_2->setModel(modal);
     s.connClose();
     qDebug()<<( modal->rowCount());

}

void detailsdisplay::on_pushButton_reset_clicked()
{
    Stocks s;
     if(!s.connOpen()){
                 qDebug()<<"Ошибка соединения";
             }
             s.connOpen();
             QSqlQuery qrys,qry;
             qrys.prepare("delete from table_sellcomplete");
        qry.prepare("Alter table table_sellcomplete AUTO_INCREMENT = 1");
             if(qrys.exec()){
                 QMessageBox::information(this,tr("Перезапуск"),tr("Перезапущено"));
                qry.exec();
                s.connClose();
             }else{
                 QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
             }
}

void detailsdisplay::on_pushButton_reset_2_clicked()
{
    Stocks s;
     if(!s.connOpen()){
                 qDebug()<<"Ошибка соединения";
             }
             s.connOpen();
             QSqlQuery qrys,qry,qr,q;
             qrys.prepare("delete from table_salerecord");
        qry.prepare("delete from sqlite_sequence where name='table_salerecord';");

             if(qrys.exec()){
                 QMessageBox::information(this,tr("Перезапуск"),tr("Перезапущено"));
                qry.exec();
                qr.exec();
                q.exec();
                s.connClose();
             }else{
                 QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
             }
}
