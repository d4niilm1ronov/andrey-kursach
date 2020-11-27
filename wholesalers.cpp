#include "wholesalers.h"
#include "ui_wholesalers.h"
#include "dashboard.h"
#include "stocks.h"
#include<QMessageBox>
#include <QDebug>

Wholesalers::Wholesalers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Wholesalers)
{
    ui->setupUi(this);

}

Wholesalers::~Wholesalers()
{
    delete ui;
}

void Wholesalers::on_pushButton_back_clicked()
{
    hide();
    Dashboard d;
    d.setModal(true);
    d.exec();
}

void Wholesalers::on_pushButton_suppentry_clicked()
{
    Stocks s;
 QString wid,wname,waddress,wphone,wemail,wmedsupply,wpostal,wcity,wcntry;
 wid = ui->lineEdit_id->text();
 wname= ui->lineEdit_supname->text();
 waddress = ui->lineEdit_address->text();
 wpostal= ui->lineEdit_postal->text();
 wcity= ui->lineEdit_city->text();
 wcntry= ui->lineEdit_country->text();
    wphone = ui->lineEdit_supphn->text();
    wemail = ui->lineEdit_supemail->text();
    wmedsupply = ui->lineEdit_medsup->text();

    if(!s.connOpen()){
        qDebug()<<"Ошибка соединения";
    }
    s.connOpen();
    QSqlQuery qrys;
    qrys.prepare("insert into table_supplier(sid,sname,saddress,postal_code,city,country,sphone,semail,smedsupply) values('"+wid+"','"+wname+"','"+waddress+"','"+wpostal+"','"+wcity+"','"+wcntry+"','"+wphone+"','"+wemail+"','"+wmedsupply+"')");
    if(qrys.exec()){
        QMessageBox::critical(this,tr("Сохранение"),tr("Сохранено"));
        s.connClose();
    }else{
        QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
}

}

void Wholesalers::on_pushButton_disp_clicked()
{
    Stocks s;
    QSqlQueryModel *m = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery *qry = new QSqlQuery(s.mydb2);
    qry->prepare("select sid as ID,sname as Customer_Name,saddress || ',' || postal_code || ',' || city ||','|| country as Address,sphone as Phone_No,semail as Email , smedsupply as Medicine_Supply from table_supplier");
    qry->exec();
    m->setQuery(*qry);
    ui->tableView->setModel(m);
    s.connClose();
    qDebug() <<( m->rowCount());


}

void Wholesalers::on_pushButton_delsupplier_clicked()
{
    Stocks s;
    QString wid;
            wid = ui->lineEdit_id->text();

            if(!s.connOpen()){
                qDebug()<<"Ошибка соединения";
            }
            s.connOpen();
            QSqlQuery qrys;
            qrys.prepare("delete from table_supplier where sid='"+wid+"'");
            if(qrys.exec()){
                QMessageBox::critical(this,tr("Удаление"),tr("Удалено"));
                s.connClose();
            }else{
                QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
            }

}

void Wholesalers::on_pushButton_search_clicked()
{
    Stocks s;
    QString srch= ui->lineEdit_search->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery* qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_supplier where sname like'%"+srch+"%' or smedsupply like'%"+srch+"%' or sid like'%"+srch+"%'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
     s.connClose();
     qDebug()<<( modal->rowCount());

}
