//
// Created by xidian on 18-7-3.
//
#include <iostream>
#include <sys/sem.h>
#include <thread>
#include <zconf.h>

key_t g_sem_key=100;
#define KEY 100
void thread31(){
    int semid =semget(KEY,1,IPC_CREAT|0666);
    g_sem_key=semid;
    if(semid<0){
        std::cout<<"error"<<std::endl;
    }
    std::cout<<"ok"<<std::endl;
    printf("%dsssss:%u\n",semid,semid);
    sleep(50);
    sembuf *smb=(sembuf*)malloc(sizeof(struct sembuf));
    smb->sem_flg=0;//wait
    smb->sem_num=0;//the first sem in semid_ds
    smb->sem_op=1;//V
    semop(semid,smb,1);
    std::cout<<"V"<<std::endl;
}

void thread32(){
    sembuf *smb=(sembuf*)malloc(sizeof(struct sembuf));
    smb->sem_flg=0;//wait
    smb->sem_num=0;//the first sem in semid_ds
    smb->sem_op=-1;//P
    semop(g_sem_key,smb,1);
    std::cout<<"P"<<std::endl;
    semctl(g_sem_key,0,IPC_RMID);
}

int testSem(){
    std::thread Thread1(&thread31);
    std::thread Thread2(&thread32);

    Thread1.join();
    std::cout<<"t1 joined"<<std::endl;
    Thread2.join();
}