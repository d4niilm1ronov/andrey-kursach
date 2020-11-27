#include "userreg.h"
#include "ui_userreg.h"
#include "stocks.h"
#include<QMessageBox>
#include<QDebug>
userreg::userreg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userreg)
{
    ui->setupUi(this);
}

userreg::~userreg()
{
    delete ui;
}


void userreg::on_pushButton_reg_clicked()
{

    Stocks s;
 QString urid,urname,upwd,uremail,urpwd,urphone;
  urname= ui->lineEdit_user->text()    ;
    urpwd = ui->lineEdit_pwd->text();
    uremail = ui->lineEdit_email->text();
    urphone = ui->lineEdit_phone->text();
        if(!s.connOpen()){
        qDebug()<<"Ошибка соединения";
    }
    s.connOpen();
    QSqlQuery qrys;
    qrys.prepare("insert into table_login(uname,upwd,uphone,uemail) values('"+urname+"','"+urpwd+"','"+urphone+"','"+uremail+"')");
    if(qrys.exec()){
        QMessageBox::information(this,tr("Сохранение"),tr("Сохранено"));
        s.connClose();
    }else{
        QMessageBox::critical(this,tr("Ошибка::"),qrys.lastError().text());
}
}
