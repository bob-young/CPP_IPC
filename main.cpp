#include <iostream>
#include <unistd.h>

int testpipe();
int testSig();
int testMsgque();
int testShm();
int testSem();

int main(int argc,char** argv){
    std::cout<<"input:0 for pipe;1 for signal;2 for msg queue;3 for shared memory;4 for semaphore"<<std::endl;
    int c=0;
    std::cin>>c;
    switch (c){
        case 0:std::cout<<"test pipe:\n";testpipe();break;
        case 1:std::cout<<"test signal:\n";testSig();break;
        case 2:std::cout<<"test msg queue:\n";testMsgque();break;
        case 3:std::cout<<"test shm:\n";testShm();break;
        case 4:std::cout<<"test sem:\n";testSem();break;
    }

    return 0;
}