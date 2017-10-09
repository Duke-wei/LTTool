#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    if(ui->usrLineEdit->text().trimmed()==tr("wengwei") &&
            ui->pwdLineEdit_2->text()==tr("123")){
   accept();
    }else{
        QMessageBox::warning(this,tr("Waring"),tr("user name or passwd error"),QMessageBox::Yes);
        ui->usrLineEdit->clear();
        ui->pwdLineEdit_2->clear();
        ui->usrLineEdit->setFocus();
    }
}
