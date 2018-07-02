#include <iostream>
#include <unistd.h>

int testpipe();
int testSig();
int testMsgque();

int main(int argc,char** argv){
    std::cout<<"input:1 for pipe;2 for signal;3 for msg queue"<<std::endl;
    int c=0;
    std::cin>>c;
    switch (c){
        case 0:std::cout<<"test pipe:\n";testpipe();break;
        case 1:std::cout<<"test signal:\n";testSig();break;
        case 2:std::cout<<"test msg queue:\n";testMsgque();break;
    }


    return 0;
}