#include "stocks.h"
#include "ui_stocks.h"
#include "dashboard.h"
#include <QDebug>
#include<QDate>
#include<QMessageBox>
#include<float.h>

Stocks::Stocks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stocks)
{
    ui->setupUi(this);

}

Stocks::~Stocks()
{
    delete ui;
}

void Stocks::on_pushButton_clicked()
{
    hide()
            ;
    Dashboard d1;
    d1.setModal(true);
    d1.exec();
}

void Stocks::on_pushButton_entrybtn_clicked()
{
    QString drid,drname,drcmpny,drqnty,drpri,drsentry,drexpdate,drtype,drcp;

            drid = ui->lineEdit_did->text();
            drname = ui->lineEdit_dname->text();
            drcmpny = ui->lineEdit_cmpny->text();
            drqnty = ui->lineEdit_qntty->text();
            drpri = ui->lineEdit_price->text();
            drsentry = ui->dateEdit_sdentry->date().toString("dd/MM/yyyy");
            drexpdate = ui->dateEdit_edentry->date().toString("dd/MM/yyyy");
            drtype = ui->lineEdit_dtype->text();
            drcp = ui->lineEdit_costprice->text();
            if(!connOpen()){
                qDebug()<<" ";
            }
            connOpen();
            QSqlQuery qrys;
            qrys.prepare("insert into table_stock(did,dname,dcmpny,dqnty,dprice,dsenty,dexpiry,dtype,dcp) values('"+drid+"'"
            ",'"+drname+"','"+drcmpny+"','"+drqnty+"','"+drpri+"','"+drsentry+"','"+drexpdate+"','"+drtype+"','"+drcp+"')");
            if(qrys.exec()){
                QMessageBox::critical(this,tr("Сохранение"),tr("Сохранено"));
                connClose();
            }else{
                QMessageBox::critical(this,tr("Ошиюка::"),qrys.lastError().text());
            }

}

void Stocks::on_pushButton_drdisplay_clicked()
{
    Stocks s;
    QSqlQueryModel *m = new QSqlQueryModel();
    connOpen();
    QSqlQuery *qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_stock");
    qry->exec();
    m->setQuery(*qry);
    ui->tableView->setModel(m);
    connClose();
    qDebug() <<( m->rowCount());
}

void Stocks::on_pushButton_updbtn_clicked()
{
    QString drid,drname,drcmpny,drqnty,drpri,drsentry,drexpdate,drtype,drcp;

            drid = ui->lineEdit_did->text();
            drname = ui->lineEdit_dname->text();
            drcmpny = ui->lineEdit_cmpny->text();
            drqnty = ui->lineEdit_qntty->text();
            drpri = ui->lineEdit_price->text();
            drsentry = ui->dateEdit_sdentry->date().toString("dd/MM/yyyy");
            drexpdate = ui->dateEdit_edentry->date().toString("dd/MM/yyyy");
            drtype = ui->lineEdit_dtype->text();
            drcp = ui->lineEdit_costprice->text();
            if(!connOpen()){
                qDebug()<<"Ошибка соединения";
            }
            connOpen();
            QSqlQuery qrys;
            qrys.prepare("update table_stock set dname='"+drname+"',dcmpny='"+drcmpny+"',dqnty='"+drqnty+"',dprice='"+drpri+"',dsenty='"+drsentry+"',dexpiry='"+drexpdate+"',dtype='"+drtype+"',dcp='"+drcp+"' where did='"+drid+"'");
            if(qrys.exec()){
                QMessageBox::critical(this,tr("Сохранение"),tr("Сохранено"));
                connClose();
            }else{
                QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
            }


}

void Stocks::on_pushButton_2_clicked()
{
    QString drid,drname,drcmpny,drqnty,drpri,drsentry,drexpdate,drtype;
            drid = ui->lineEdit_did->text();

            if(!connOpen()){
                qDebug()<<"Ошибка соединения";
            }
            connOpen();
            QSqlQuery qrys,qry;
            qrys.prepare("delete from table_stock where did='"+drid+"'");
            qry.prepare("UPDATE SQLITE_SEQUENCE SET SEQ=0 WHERE NAME='table_stock'");
            if(qrys.exec()){
                qry.exec();
                QMessageBox::critical(this,tr("Удаленение"),tr("Удалено"));
                connClose();
            }else{
                QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
            }

}

void Stocks::on_tableView_activated(const QModelIndex &index)
{

    QString val = ui->tableView->model()->data(index).toString();
    if(!connOpen()){
        qDebug()<<"Ошибка соединие с базой данных";
        return;
    }
    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from table_stock where did= '"+val+"' or dname= '"+val+"' or dcmpny= '"+val+"'or dqnty= '"+val+"' or dprice= '"+val+"'or dsenty= '"+val+"' or dexpiry= '"+val+"'or dtype= '"+val+"'");
    if(qry.exec()) {
        while(qry.next())
        {
            ui->lineEdit_did->setText(qry.value(0).toString());
            ui->lineEdit_dname->setText(qry.value(1).toString());
            ui->lineEdit_cmpny->setText(qry.value(2).toString());
            ui->lineEdit_qntty->setText(qry.value(3).toString());
            ui->lineEdit_price->setText(qry.value(4).toString());
            ui->dateEdit_sdentry->setDate(qry.value(5).toDate());
            ui->dateEdit_edentry->setDate(qry.value(6).toDate());
            ui->lineEdit_dtype->setText(qry.value(7).toString());

        }
        connClose();
    }else {
       QMessageBox::critical(this,tr("Ошибка::"),qry.lastError().text());
    }

}



void Stocks::on_pushButton_3_clicked()
{
    Stocks s;
    QString srch= ui->lineEdit_search->text();
    QSqlQueryModel * modal = new QSqlQueryModel();
    connOpen();
    QSqlQuery* qry = new QSqlQuery(s.mydb2);
    qry->prepare("select *from table_stock where dname like'%"+srch+"%' or dcmpny like'%"+srch+"%' or did like'%"+srch+"%' ");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
     connClose();
     qDebug()<<( modal->rowCount());
}
