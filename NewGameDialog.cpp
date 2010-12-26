#include"NewGameDialog.h"
#include"util.h"
NewGameDialog::NewGameDialog(int row,int col,int num, QWidget *parent):QDialog(parent){
    this->setupUi(this);
    this->setWindowIcon(QIcon(":/images/img/new.png"));
    QRegExp num2("[0-9]{0,2}"),num3("[0-9]{0,3}");
    this->rowText->setValidator(new QRegExpValidator(num2,this));
    this->columnText->setValidator(new QRegExpValidator(num2,this));
    this->mineText->setValidator(new QRegExpValidator(num3,this));
    if(row!=-1 && col!=-1 && num!=-1){
        this->rowText->setText(qstr(row));
        this->columnText->setText(qstr(col));
        this->mineText->setText(qstr(num));
    }
}
