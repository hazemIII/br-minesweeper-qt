#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include<QDialog>
#include"ui_NewGameDialog.h"

class NewGameDialog : public QDialog, public Ui::NewGameDialog{
    Q_OBJECT
public:
    NewGameDialog(int row=-1,int col=-1,int num=-1,QWidget* parent=0);
};

#endif // NEWGAMEDIALOG_H
