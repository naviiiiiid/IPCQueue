//
// Created by N_Soorani on 12/3/2022.
//
#include <cstdio>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>

#ifndef UNTITLED6_QUEUE_H
#define UNTITLED6_QUEUE_H

using namespace std;

enum TYPE {CREATE , GET};

class IPCQueue {
private:

    int qid;
    template <class T> int getQ(T *item , int msgtype , int size);


public:
    explicit IPCQueue(key_t key , TYPE mode){

         if(mode == CREATE){
             this->qid = msgget(key, 0666 | IPC_CREAT);
         }
         else if(mode == GET){
             this->qid = key;
         }
    }

    int getQid() const{

        return this->qid;
    }

    ~IPCQueue() {
        printf("object is destroyed!\n");
    }

    template <class T> int putQ(T *item ,int size);
    template <class T> int getQByType(T *item , int msgtype , int size);
    template <class T> int getQFirst(T *item , int size);
    template <class T> int getQLowerType(T *item , int msgtype , int size);
};

template <class T> int IPCQueue::getQ(T *item , int msgtype , int size) {

    if (msgrcv(qid, (T *)item, size, msgtype,MSG_NOERROR) == -1) {
        if (errno != ENOMSG) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;
    }
}


template <class T> int IPCQueue::putQ(T *item , int size) {

    if (msgsnd(qid, (T *)item, size, IPC_NOWAIT) == -1) {
        perror("msgsnd error");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


template <class T> int IPCQueue::getQByType(T *item , int msgtype , int size) {

    if(msgtype <= 0) {
        printf("msgtype is zero or negative \n");
        exit(EXIT_FAILURE);
    }

    return getQ<T>(item , msgtype , size);
}


template <class T> int IPCQueue::getQFirst(T *item , int size) {

    memset(item, 0, sizeof(T));
    return getQ<T>(item, 0, size);

}


template <class T> int IPCQueue::getQLowerType(T *item , int msgtype , int size) {

    if(msgtype >= 0) {
        printf("msgtype is zero or positive \n");
        exit(1);
    }

    return getQ<T>(item , msgtype , size);
}


#endif //UNTITLED6_QUEUE_H
