#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include<QDialog>
#include"ui_NewGameDialog.h"
#include"Player.h"

class NewGameDialog : public QDialog, public Ui::NewGameDialog{
    Q_OBJECT
public:
    QString p1,p2;
    NewGameDialog(int row=-1,int col=-1,int num=-1,QWidget* parent=0);
private slots:
    void selectPlayer1(QString s);
    void selectPlayer2(QString s);
};

#endif // NEWGAMEDIALOG_H
