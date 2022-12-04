#include <bits/stdc++.h>
#include <getopt.h>
#include "IPCQueue.h"
using namespace std;

struct message {
    long type;
    char text[20];
};

void getQ(int argc, char *argv[] , key_t qid , TYPE type) {

    message msg{};

    IPCQueue ipcQueue(qid, type);

    if(ipcQueue.getQFirst<message>(&msg, sizeof(message)) == EXIT_FAILURE ){
        printf("message is not received from queue id  = %d message  = %s !\n", ipcQueue.getQid() ,msg.text  );
        exit(EXIT_FAILURE);
    }
    printf("message received from queue id =  %d message  = %s \n", ipcQueue.getQid() , msg.text );
}
void putQ(int argc, char *argv[] , key_t qid , TYPE type) {

    message msg{};
    memset(&msg, 0, sizeof(message));
    msg.type = 100;
    memcpy(msg.text, argv[4], sizeof(msg.text));

    IPCQueue ipcQueue(qid, type);
    if(ipcQueue.putQ<message>(&msg, sizeof(message)) == EXIT_FAILURE ) {
        printf("message is not sent to queue id = %d message  = %s !\n", ipcQueue.getQid() , msg.text);
        exit(EXIT_FAILURE);
    }
    printf("message is sent to queue id =  %d message  = %s \n", ipcQueue.getQid() , msg.text);
}
void showHelp(){

    printf("\narg1 -s for send to queue \n -r received from queue \n -h help \n");
    printf("arg2 qid \n");
    printf("arg3 type { '0'  = create queue , '1'  = get queue } \n");
    printf("arg4 message  \n");

}

int main(int argc, char *argv[]) {

    if(argc < 4) {
        printf("argument is lower than 3! "); showHelp();
        exit(EXIT_FAILURE);
    }

    key_t qid = atoi(argv[2]);
    int type = atoi(argv[3]);
    int  opt;

    while ((opt = getopt(argc, argv, "srh:k:")) != -1) {
        switch (opt) {
            case 's':
                putQ(argc, argv, qid , (TYPE)type);
                break;
            case 'r':
                getQ(argc, argv, qid , (TYPE)type);
                break;
            case 'h':
                showHelp();
                break;
            default:
                showHelp();
        }
    }
    return 0;
}