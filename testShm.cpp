//
// Created by xidian on 18-7-2.
//

#include <thread>
#include <iostream>
#include <sys/shm.h>
#include <cstring>
#include <zconf.h>
#include <sys/ipc.h>

#define PERM S_IRUSR|S_IWUSR|IPC_CREAT
int g_shmid=0;
void thread21(){
    int shmid=shmget(IPC_PRIVATE,1024,IPC_CREAT|0666);
    if(shmid==-1){
        std::cout<<"create error\n";
    }else{
        g_shmid=shmid;
        std::cout<<"create ok\n";
    }

    const char* msg="hello world\0";
    void *waddr=shmat(shmid,0,0);
    memset(waddr,'\0',1024);

    memcpy(waddr,msg,12);
    std::cout<<"write ok\n";
    pthread_exit(0);
}

void thread22(){
    while(g_shmid==0){
        sleep(1);
    }
    void* raddr=shmat(g_shmid,0,0);
    std::cout<<"shmget:"<<(char*)raddr<<std::endl;
    shmctl(g_shmid,IPC_RMID,NULL);
    pthread_exit(0);
}

int testShm(){
    std::thread Thread1(&thread21);
    std::thread Thread2(&thread22);

    Thread1.join();
    Thread2.join();
}