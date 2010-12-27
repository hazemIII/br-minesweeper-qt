#include"MainWindow.h"
int MsButton::state=0;
MainWindow* MsButton::gui=0;

MsButton::MsButton(QWidget* parent,int _i, int _j)
    :QPushButton(parent),i(_i),j(_j){}

void MsButton::mousePressEvent(QMouseEvent *e){
    try{
        if(e->button()==Qt::LeftButton){
            gui->sunkWidgetsIfUnknown(i,j);
            if(state==0)
                state=1;
            else if(state==2){
                state=3;
                gui->sunkNeighbourWidgets(i,j);
            }
        }else if(e->button()==Qt::RightButton){
            if(state==0){
                state=2;
                gui->toggle(i,j);
            }else if(state==1){
                state=3;
                gui->sunkNeighbourWidgets(i,j);
            }
        }
    }catch(std::exception e){
        //do nothing
    }
}
void MsButton::mouseReleaseEvent(QMouseEvent *e){
    try{
        if(e->button()==Qt::LeftButton){
            gui->raiseWidgetsIfUnknown(i,j);
            if(state==1){
                state=0;
                gui->dig(i,j);
            }else if(state==3){
                state=4;
                gui->raiseNeighbourWidgets(i,j);
                gui->explore(i,j);
            }else if(state==4)
                state=0;
        }else if(e->button()==Qt::RightButton){
            if(state==2)
                state=0;
            else if(state==3){
                state=4;
                gui->raiseNeighbourWidgets(i,j);
                gui->explore(i,j);
            }else if(state==4)
                state=0;
        }
    }catch(std::exception e){
        //also do nothing
    }
}

