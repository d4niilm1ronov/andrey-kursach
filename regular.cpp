#include "regular.h"
#include "ui_regular.h"
#include "dashboard.h"
#include "stocks.h"
#include<QDebug>
#include<QMessageBox>

regular::regular(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regular)
{
    ui->setupUi(this);
}

regular::~regular()
{
    delete ui;
}

void regular::on_pushButton_back_clicked()
{
    hide();
    Dashboard d;
    d.setModal(true);
    d.exec();
}

void regular::on_pushButton_back_2_clicked()
{
    Stocks s;
 QString rid,rname,rdname,rphmn,rcost,rdue,raddress;
 rid = ui->lineEdit_id->text();
  rname = ui->lineEdit_name->text()    ;
 rdname = ui->lineEdit_dname->text();
    rphmn = ui->lineEdit_phone->text();
    rcost = ui->lineEdit_cost->text();
    rdue = ui->lineEdit_due->text();
    raddress = ui->lineEdit_address->text();

    if(!s.connOpen()){
        qDebug()<<"Ошибка соединения";
    }
    s.connOpen();
    QSqlQuery qrys;
    qrys.prepare("insert into table_regular(id,name,drug_name,phone_number,cost,due,address) values('"+rid+"','"+rname+"','"+rdname+"','"+rphmn+"','"+rcost+"','"+rdue+"','"+raddress+"')");
    if(qrys.exec()){
        QMessageBox::critical(this,tr("Сохранение"),tr("Сохранено"));
        s.connClose();
    }else{
        QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
}

}

void regular::on_pushButton_back_4_clicked()
{
    Stocks s;
    QSqlQueryModel *m = new QSqlQueryModel();
    s.connOpen();
    QSqlQuery *qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_regular");
    qry->exec();
    m->setQuery(*qry);
    ui->tableView->setModel(m);
    s.connClose();
    qDebug() <<( m->rowCount());
}

void regular::on_pushButton_search_clicked()
{
    {
        Stocks s;
        QString srch= ui->lineEdit_search->text();
        QSqlQueryModel * modal = new QSqlQueryModel();
        s.connOpen();
        QSqlQuery* qry = new QSqlQuery(s.mydb2);
        qry->prepare("select *from table_regular where name like'%"+srch+"%' or drug_name like'%"+srch+"%' or id like'%"+srch+"%'");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
         s.connClose();
         qDebug()<<( modal->rowCount());

    }

}

void regular::on_pushButton_back_3_clicked()
{
    Stocks s;
 QString rid,rname,rdue;
 rid = ui->lineEdit_id->text();
  rname = ui->lineEdit_name->text()    ;
    rdue = ui->lineEdit_due->text();

    if(!s.connOpen()){
        qDebug()<<"Ошибка соединения";
    }
    s.connOpen();
    QSqlQuery qrys;
    qrys.prepare("update table_regular set due= due+'"+rdue+"' where id='"+rid+"')");
    if(qrys.exec()){
        QMessageBox::critical(this,tr("Сохрение"),tr("Сохранено"));
        s.connClose();
    }else{
        QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
}
}
