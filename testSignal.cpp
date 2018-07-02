//
// Created by xidian on 18-6-29.
//

#include <iostream>
#include <csignal>
#include <thread>
#include <zconf.h>
int g=0;
void thread0(int signum){
    std::cout<<"signal :"<<signum<<std::endl;
    if(signum==SIGINT)
    exit(SIGINT);
}
void thread1(){
    signal(2,thread0);
    int i=3;
    while(i++) {
        sleep(10);
        std::cout << "thread 1 sleeping" << g++<<std::endl;
    }
}

void thread2(){
    int i=4;
    while(i--){
    sleep(4);
    std::cout<<"thread 2 sleeping"<< g++<<std::endl;
    }
    raise(2);
}

int testSig(){

    std::thread Thread1(&thread1);
    std::thread Thread2(&thread2);

    Thread1.join();
    Thread2.join();
}