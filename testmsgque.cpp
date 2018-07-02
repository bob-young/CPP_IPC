//
// Created by xidian on 18-7-2.
//
#include <iostream>
#include <thread>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <cstring>
#include <zconf.h>

#pragma pack(1)
struct msgbody{
    char name[10]={0};
    int state=0;
    int type=0;
    unsigned char msg[1024];
};
#pragma pack()
int T_MSGKEY=1024;


//----------------------------------- System V ------------------------------
//based on ipc.h
//get a msgque:int msgget(key_t key,int msg_flag)
//      flag=IPC_EXCL get an ipc id
//      flag=IPC_CREAT create an IPC msgque
//send msg:     int msgsend(int msgid,const void* msg_ptr,size_t size,int msg_flag)
//receive msg:  int msgrcv(int msgid,void* msg_ptr,size_t size,long msg_type,int msg_flag)
//msgque control: int msgctl(int msgid,int command ,struct msgid_ds *buf)
//          command=IPC_RMID destroy msgque
//          command=IPC_SET  set current msgque id using msgid_ds
//          command=IPC_STAT set current msgque msgid_ds using msgid
void thread11(){//sender
    //create msg
    msgbody msg;
    memcpy(msg.name,"test1\0",6);
    msg.state=1;
    msg.type=1;

    const char* msg_send="hello world!\0";
    memcpy(msg.msg,msg_send,13);
    int flag_msg_creat;
    flag_msg_creat=msgget(T_MSGKEY,IPC_EXCL);
    if(flag_msg_creat<0){
        //not exist
        flag_msg_creat=msgget(T_MSGKEY,IPC_CREAT|0666);//create
        if(flag_msg_creat<0){//fail create
            std::cout<<"failed to create msgque\n";
            pthread_exit(0);
        } else{
            //succeed

        }
    }

    //use
    int msg_id=flag_msg_creat;
    int flag_msg_send=msgsnd(msg_id,&msg,sizeof(struct msgbody),IPC_NOWAIT);
    if(flag_msg_send<0){
        std::cout<<"send failure\n";
        pthread_exit(0);
    }
    std::cout<<"sender:"<<msg.msg<<std::endl;


}

void thread12(){//receiver
    msgbody msgbody1;
    //sleep(1);
    int flag_msg_create=msgget(T_MSGKEY,IPC_EXCL);
    if(flag_msg_create<0){
        std::cout<<"no such msgque\n";
    }
    int msg_id=flag_msg_create;
    int flag_msg_rec=msgrcv(msg_id,&msgbody1,sizeof(struct msgbody),0,0);
    std::cout<<"receiver:length="<<flag_msg_rec<<std::endl;
    std::cout<<msgbody1.msg<<std::endl;
    msgctl(msg_id,IPC_RMID,0);
}
//----------------------------------- System V ------------------------------
int testMsgque(){
    std::thread Thread1(&thread11);
    std::thread Thread2(&thread12);

    Thread1.join();
    Thread2.join();
}