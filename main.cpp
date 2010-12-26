#include<QApplication>
#include"MainWindow.h"

#if MODE==GUI_MODE

int main(int argc,char** argv){
    QApplication app(argc,argv);
    MainWindow *win=new MainWindow();
    win->show();
    return app.exec();
}

#endif
