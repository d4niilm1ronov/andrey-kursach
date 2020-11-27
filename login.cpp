#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include "stocks.h"
#include "userreg.h"
LOGIN::LOGIN(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LOGIN)
{
    ui->setupUi(this);
     Stocks conn;
}

LOGIN::~LOGIN()
{
    delete ui;
}

void LOGIN::on_pushButton_login_clicked()
{
    Stocks conn;
    QString username = ui->lineEdit_usrname->text();
    QString password = ui->lineEdit_pwd->text();
    conn.connOpen();
    if(!conn.connOpen()){
        qDebug()<<"Ошибка открытия";
        return;
    }
    QSqlQuery qry;
    qry.prepare("select *from table_login where uname= '"+username+"'and upwd='"+password+"'");
    if(qry.exec()){
        int count=0;
        while (qry.next()) {
            count++;
            }
        if(count!=0 ){
            conn.connClose();
            hide();
            dsh = new Dashboard(this);
            dsh->show();
        }else {
        QMessageBox::warning(this,"Login","Неправильный логин и пароль");
    }
    }


}

void LOGIN::on_pushButton_reg_clicked()
{
    userreg w ;
    w.setModal(true);
    w.exec();

}
