#include "Naubf.hpp"
#include <fstream>
#include <sstream>

enum AvailableTypes{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_NONE
};

std::string typeNames[] = {
    "char",
    "int",
    "float"
};
int nCells = 3000;
AvailableTypes curType = TYPE_CHAR;
bool bVerbose = false;

template<typename T>
void parseFile(std::string & _src){
    Naubf<T> naubf(nCells);
    naubf.parseSrc(_src, false);
}

void parseFile(std::string & _src, AvailableTypes _curType){
    switch(_curType){
        case TYPE_CHAR:
            parseFile<char>(_src);
            break;
        case TYPE_INT:
            parseFile<int>(_src);
            break;
        case TYPE_FLOAT:
            parseFile<float>(_src);
            break;
        default:
            break;
    }
}

void parseFile(char * _pth){
    std::ifstream f(_pth);
    std::stringstream buf;
    std::string src;
    buf<<f.rdbuf();
    src = buf.str();
    parseFile(src, curType);
    Naubf<char> naubf(nCells);
    naubf.parseSrc(src, false);
}

template<typename T>
void prompt(Naubf<T> & _bf){
    std::string s;
    std::cout<<"[naubf]:: ";
    std::cin >> s;
    
    _bf.parseSrc(s, bVerbose);
}

template<typename T>
void startInteractive(){
    Naubf<T> naubf(nCells);
    while(1){
        prompt<T>(naubf);
    }
}

void startInteractive(){
    std::cout<<"-Interactive interpreter mode-"<<std::endl;
    std::cout<<"    - tape size: "<<nCells<<std::endl;
    std::cout<<"    - cell type: "<<typeNames[(int)curType]<<std::endl;
    std::cout<<"[new line to run current line]"<<std::endl;
    std::cout<<"[ctrl-c to exit              ]"<<std::endl;
    
    switch(curType){
        case TYPE_CHAR:
            startInteractive<char>();
            break;
        case TYPE_INT:
            startInteractive<int>();
            break;
        case TYPE_FLOAT:
            startInteractive<float>();
            break;
        default:
            break;
    }

}

void printWelcome(){
    std::cout<<"===================================="<<std::endl;
    std::cout<<"naubf - NotActuallyUsingBrainFuck"<<std::endl;
    std::cout<<"- a templated, circular, extandable-"<<std::endl;
    std::cout<<"- brainfuck interpreter            -"<<std::endl;
    std::cout<<"===================================="<<std::endl;
}

void printHelp(){
    std::cout<<"____________________________________"<<std::endl;
    std::cout<<"Usage:"<<std::endl;
    std::cout<<"-h              this help screen"<<std::endl;
    std::cout<<"-v              verbose"<<std::endl;
    std::cout<<"-f              pass a source file"<<std::endl;
    std::cout<<"[no options]    interactive mode"<<std::endl;
    std::cout<<"____________________________________"<<std::endl;

}

bool isOption(std::string & _s){
    if(_s.size()>1){
        if(_s[0]=='-'){
            return true;
        }
    }
    return false;
}

void parseTypeArgument(std::string _s){
    for(int i=0;i<(int)TYPE_NONE;i++){
        if(_s==typeNames[i]){
            curType = (AvailableTypes)i;
            return;
        }
    }
}

void parseArguments(int argc, char * argv[]){
    
    for(int i=1;i<argc;i++){
        std::string _arg(argv[i]);
        if(isOption(_arg)){
            switch(_arg[i]){
                case 'h':
                    printHelp();
                    break;
                case 'v':
                    bVerbose = true;
                    break;
                case 'f':
                    if(i<(argc-1)){
                        parseFile(argv[i+1]);
                    }
                    return;
                    break;
                case 's': 
                    if(i<(argc-1)){
                        nCells = atoi(argv[i+1]);
                        i++;
                    }
                    break;
                case 't':
                    if(i<(argc-1)){
                        parseTypeArgument(std::string(argv[i+1]));
                        i++;
                    }
                    break;
                default:
                    printHelp();
                    break;
            }
        }else{
            parseFile(argv[i]);
            return;
        }
    }
    startInteractive();
}

int main(int argc, char * argv[]){
    printWelcome();
    if(argc>1){
        parseArguments(argc, argv);
    }else{
        startInteractive();
    }
}
