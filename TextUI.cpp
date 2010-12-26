#include"NormalGameLogic.h"
using namespace std;
#if MODE==TEXTUI_MODE
void usage(){
    cout<<"	new <row> <col> <num>			start a new game"<<endl;
    cout<<"	dig <row> <col>				dig cell (<row>,<col>)"<<endl;
    cout<<"	mark <row> <col>			mark cell (<row>,<col>)"<<endl;
    cout<<"	unmkar <row> <col>			unmark cell (<row>,<col>)"<<endl;
    cout<<"	explore <row> <col>			explore neighbours of cell (<row>,<col>)"<<endl;
    cout<<"	exit					exit game"<<endl;
}
int main(){
    GameLogic *gl=new NormalGameLogic();
    usage();
    while(1){
        cout<<gl->toString()<<endl;
        if(gl->checkWin()){
            cout<<"Congratulations! You Win!!"<<endl;
        }else if(gl->checkLose()){
            cout<<"Better luck next time  :)"<<endl;
        }
        cout<<"> ";
        string s,cmd;
        stringstream ss;
        if(!getline(cin,s)) break;
        try{
            ss<<s;
            ss>>cmd;
            if(cmd=="new"){
                int row,col,num;
                ss>>row>>col>>num;
                if(ss.fail()){
                    printErr("invalid argument: "+s);
                    continue;
                }
                gl->newGame(row,col,num);
            }else if(cmd=="dig"){
                int row,col;
                ss>>row>>col;
                if(ss.fail()){
                    printErr("invalid argument: "+s);
                    continue;
                }
                gl->dig(row,col);
            }else if(cmd=="mark"){
                int row,col;
                ss>>row>>col;
                if(ss.fail()){
                    printErr("invalid argument: "+s);
                    continue;
                }
                gl->mark(row,col);
            }else if(cmd=="unmark"){
                int row,col;
                ss>>row>>col;
                if(ss.fail()){
                    printErr("invalid argument: "+s);
                    continue;
                }
                gl->unmark(row,col);
            }else if(cmd=="explore"){
                int row,col;
                ss>>row>>col;
                if(ss.fail()){
                    printErr("invalid argument: "+s);
                    continue;
                }
                gl->explore(row,col);
            }else if(cmd=="cheat"){
                cout<<gl->cheat();
            }else if(cmd=="exit"){
                cout<<"Bye"<<endl;
                break;
            }else{
                printErr("Unknown command: "+s);
            }
        }catch(exception e){
            cout<<"unexpected exception caught:"<<endl;
            cout<<e.what()<<endl;
        }


    }
    delete[] gl;
    return 0;
}
#endif
