#include"NewGameDialog.h"
#include"util.h"
NewGameDialog::NewGameDialog(int row,int col,int num, QWidget *parent):QDialog(parent){
    this->p1="Human";
    this->p2="Human";
    this->setupUi(this);
    connect(this->player1ComboBox,SIGNAL(activated(QString)),this,SLOT(selectPlayer1(QString)));
    connect(this->player2ComboBox,SIGNAL(activated(QString)),this,SLOT(selectPlayer2(QString)));
    this->selectPlayerGroupBox->hide();
    this->setWindowIcon(QIcon(":/images/img/new.png"));
    QRegExp num2("[0-9]{0,2}"),num4("[0-9]{0,4}");
    this->rowText->setValidator(new QRegExpValidator(num2,this));
    this->columnText->setValidator(new QRegExpValidator(num2,this));
    this->mineText->setValidator(new QRegExpValidator(num4,this));
    if(row!=-1 && col!=-1 && num!=-1){
        this->rowText->setText(qstr(row));
        this->columnText->setText(qstr(col));
        this->mineText->setText(qstr(num));
    }
}
void NewGameDialog::selectPlayer1(QString s){
    p1=s;
}void NewGameDialog::selectPlayer2(QString s){
    p2=s;
}
