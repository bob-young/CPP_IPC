pipe fifo signal mq shm sem

System V 标准的shared memory ,message queue,semaphore 都是基于sys/ipc.h实现，因此存在很多共同点
有源码可知，他们都由一个struct xxxid_ds 管理，每个xxxid_ds 对应了一个struct ipc_ids,又对应了内核中的ipc_kernel。
以msg为例：
msgget()返回一个int 对应其msgid_ds，他管理着一个msgbuf数组（即msg中的数据指针），又有对应的ipc_ids，在内核中有对应的 shmid_kernel ，内核统一管理这些shmid_kernel。
同时，他们的创建 shmget、semget、msgget都是基于ipc_get_new()实现，创建需要两个关键参数key_t KEY ，struct perm：

key 是我们创建输入的key，key以自定义也可以用ftok(char* fp,int dname),ftok()基于文件或文件夹路径(inode)，获取stat，与dname合并成key，由源码知：
key = dname&FF00 0000 | stat.st_dev&00FF 0000 | stat.st_ino&0000 FFFF 
因此dname不同可以让多个ipc_ids基于一个filepath。

perm 是我们输入flag时产生的控制结构体，操作方式，权限控制等。要注意在创建时，IPC_CREAT|0666，0666是权限掩码，其原理同chmod
每个ipc_ids关联一个perm
