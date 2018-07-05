//
// Created by xidian on 18-6-19.
//

#include <iostream>
#include <unistd.h>

void father(int pr){
    char a[100];
    char* aa=a;
    ssize_t len;
    while(1){
        len=read(pr,aa++,1);
        std::cout << "\nreceive :"<<len<<std::endl ;
        if(*(aa-1)=='\0'){ break;}

    }
    //read(pr,a,100);
    std::cout << "father got:" << a << std::endl;
}

void son(int pw){

    const char* buff="oh my father i am your son";
    std::cout << "son sending..." <<(buff)<< std::endl;
    while (1){
        sleep(1);
        std::cout << "sleeping...\n";
        write(pw,buff,28);

        close(pw);
        break;
    }
    std::cout << "son exit...\n";
    exit(0);
}

int testpipe() {
    int mypipe[2];
    int p=pipe(mypipe);
    if(p<0){
        std::cout << "can not create pipe!" << std::endl;
    }

    pid_t pid=fork();
    if(pid>0){
        std::cout << "father create:" << pid<< std::endl;
        father(mypipe[0]);//out
    }else{
        std::cout << "son get:" << pid<< std::endl;
        son(mypipe[1]);//in

    }

    return 0;
}