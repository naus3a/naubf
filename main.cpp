#include "Naubf.hpp"
#include <fstream>
#include <sstream>

bool bVerbose = false;

void parseFile(char * _pth){
    std::ifstream f(_pth);
    std::stringstream buf;
    std::string src;
    buf<<f.rdbuf();
    src = buf.str();
    Naubf<char> naubf;
    naubf.parseSrc(src, false);
}

template<typename T>
void prompt(Naubf<T> & _bf){
    std::string s;
    std::cout<<"[naubf:]";
    std::cin >> s;
    
    _bf.parseSrc(s, bVerbose);
}

void startInteractive(){
    std::cout<<"-Interactive interpreter mode-"<<std::endl;
    std::cout<<"[new line to run current line]"<<std::endl;
    std::cout<<"[ctrl-c to exit              ]"<<std::endl;
    Naubf<char> naubf;
    while(1){
        prompt<char>(naubf);
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
                    startInteractive();
                    break;
                case 'f':
                    if(i<(argc-1)){
                        parseFile(argv[i+1]);
                    }
                    return;
                    break;
                default:
                    printHelp();
                    break;
            }
        }else{
            printHelp();
        }
    }
}

int main(int argc, char * argv[]){
    printWelcome();
    if(argc>1){
        parseArguments(argc, argv);
    }else{
        startInteractive();
    }
}
