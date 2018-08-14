//naubf
// NotActuallyUsingBrainFuck
// written by enrico<naus3a>viola in aug 2018
// naus3a@gmail.com
// http://naus3a.ml
// naus3a on github, twitter and basically everywhere else
// license: MIT
//

#include <iostream>

template<typename T>
class Naubf {
public:
    Naubf(int _nCells=30000){
        tape = NULL;
        makeTape(_nCells);
    }
    ~Naubf(){destroyTape();}

    void makeTape(int _nCells){
        destroyTape();
        nCells = _nCells;
        tape = new T[nCells];
        curPos = 0;
    }
    
    void pointerUp(bool _bVerbose=false){
        curPos++;
        if(curPos>=nCells)curPos=0;
        if(_bVerbose)std::cout<<"---> pointer set to "<<curPos<<std::endl;
    }

    void pointerDown(bool _bVerbose=false){
        curPos--;
        if(curPos<0)curPos=nCells-1;
        if(_bVerbose)std::cout<<"---> pointer set to "<<curPos<<std::endl;
    }
    
    void valueUp(bool _bVerbose=false){
        tape[curPos]++;
        if(_bVerbose)std::cout<<"---> value @"<<curPos<<" set to "<<(int)tape[curPos]<<std::endl;
    }
    
    void valueDown(bool _bVerbose=false){
        tape[curPos]--;
        if(_bVerbose)std::cout<<"---> value @"<<curPos<<" set to "<<(int)tape[curPos]<<std::endl;
    }

    virtual void output(bool _bVerbose=false){std::cout<<tape[curPos];}
    virtual void input(bool _bVerbose=false){std::cin>>tape[curPos];}

    virtual void open(std::string & _src, int & sId, bool _bVerbose=false){
        if(tape[curPos]==0){
            for(int i=sId;i<_src.size();i++){
                if(_src[i]==']'){
                    sId = i+1;
                    if(_bVerbose)std::cout<<"---> jumped past ]"<<std::endl;
                    return;
                }
            }
        }
    }

    virtual void close(std::string & _src, int & sId,  bool _bVerbose=false){
        if(tape[curPos]!=0){
            for(int i=sId;i>=0;i--){
                if(_src[i]=='['){
                    sId = i;
                    if(_bVerbose)std::cout<<"---> jumped past ["<<std::endl;
                    return;
                }
            }
        }
    }
    
    void parseSrc(std::string & _src, bool _bVerbose=false){
        for(int i=0;i<_src.size();i++){
            switch(_src[i]){
                case '<':
                    pointerDown(_bVerbose);
                    break;
                case '>':
                    pointerUp(_bVerbose);
                    break;
                case '+':
                    valueUp(_bVerbose);
                    break;
                case '-':
                    valueDown(_bVerbose);
                    break;
                case '.':
                    output(_bVerbose);
                    break;
                case ',':
                    input(_bVerbose);
                    break;
                case '[':
                    open(_src, i, _bVerbose);
                    break;
                case ']':
                    close(_src, i, _bVerbose);
                    break;
                default:
                    break;
            }
        }
    }


    void parseSrc(std::string & _src){
        for(int i=0;i<_src.size();i++){
            switch(_src[i]){
                case '<':
                    pointerDown();
                    break;
                case '>':
                    pointerUp();
                    break;
                case '+':
                    valueUp();
                    break;
                case '-':
                    valueDown();
                    break;
                case '.':
                    output();
                    break;
                case ',':
                    input();
                    break;
                case '[':
                    open();
                    break;
                case ']':
                    close();
                    break;
                default:
                    break;
            }
        }
    }
protected:
    void destroyTape(){
        if(tape != NULL){
            delete [] tape;
        }
    }

    T * tape;
    int curPos;
    int nCells;
};

