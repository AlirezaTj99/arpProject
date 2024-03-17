#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h> 
#include <fcntl.h>
#include <sys/mman.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include "./../include/master.h"

#include <sys/shm.h>
#include <semaphore.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <bits/sigaction.h>

float ee_x=0.0, ee_y=0.0;bool masterTerminate = 0;
int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;
int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10;
int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10;
// char format_buffer[160]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
bool clientErr = 0;
bool reachedAllTheGoals = 0;

void error(char *msg)
{
    clientErr = 1;

    perror(msg);
}

// void block_signal(int signal)
// {
//     /*
//     A function that blocks the signal specified in the function argument.
//     */

//     // Create a set of signals to block
//     sigset_t sigset;

//     // Initialize the set to 0
//     sigemptyset(&sigset);

//     // Add the signal to the set
//     sigaddset(&sigset, signal);

//     // Add the signals in the set to the process' blocked signals
//     sigprocmask(SIG_BLOCK, &sigset, NULL);
// }


// void unblock_signal(int signal)
// {
//     /*
//     A function that unblocks the signal specified in the function argument.
//     */
   
//     // Create a set of signals to unblock
//     sigset_t sigset;

//     // Initialize the set to 0
//     sigemptyset(&sigset);

//     // Add the signal to the set
//     sigaddset(&sigset, signal);

//     // Remove the signals in the set from the process' blocked signals
//     sigprocmask(SIG_UNBLOCK, &sigset, NULL);
// }

int main(int argc, char *argv[])
{

    int fd4;
    char * myfifo4 = "/tmp/myfifo4";
    mkfifo(myfifo4, 0666);
    char str4[80];
    char format_string4[80]="%d,%d";

    int fd5;
    char * myfifo5 = "/tmp/myfifo5";
    mkfifo(myfifo5, 0666);

    int fd7;
    char * myfifo7 = "/tmp/myfifo7";
    mkfifo(myfifo7, 0666);

    int fd8;
    char * myfifo8 = "/tmp/myfifo8";
    mkfifo(myfifo8, 0666);

    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char rbuffer[256];


    // // Spawn obstacle Process
    // char *arg_list_obstacle[] = {"/usr/bin/konsole", "-e", "./bin/obstacle", NULL};
    // pid_t pid_obstacle = spawn("/usr/bin/konsole", arg_list_obstacle);

    // // Spawn goal Process
    // char *arg_list_goal[] = {"/usr/bin/konsole", "-e", "./bin/goal", NULL};
    // pid_t pid_goal = spawn("/usr/bin/konsole", arg_list_goal);
    
    while(1){
        server = NULL;
        while (server == NULL) {
            if (argc < 3) {
                fprintf(stderr,"usage %s hostname port\n", argv[0]);
                error("argv");
            }
            portno = atoi(argv[2]);
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) 
                error("ERROR opening socket");
            server = gethostbyname(argv[1]);
            if (server == NULL) {
                fprintf(stderr,"ERROR, no such host\n");
            }
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
            (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
            error("ERROR connecting");
        bzero(buffer,256);


        strcpy(buffer, "OI");
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
            error("ERROR writing to socket");

        bzero(rbuffer,256);
        // usleep(100);
        n = read(sockfd,rbuffer,sizeof(rbuffer));
        usleep(100);
        printf("bufferread1: %s  \n", buffer);
        if (n < 0) 
            error("ERROR reading from socket");

        bzero(rbuffer,256);
        usleep(100);
        printf("bufferread11111: %s  \n", rbuffer);
        n = read(sockfd,rbuffer,sizeof(rbuffer));
        printf("bufferread2: %s  \n", rbuffer);
        n = write(sockfd,rbuffer,strlen(rbuffer));
        if (n < 0) 
            error("ERROR reading from socket");
        fd4 = open(myfifo4,O_WRONLY);                                                               // Write window siza to obstacle
        if (fd4 == -1) {
            perror("Error opening FIFO4");
        }
        write(fd4, rbuffer, 80);
        close(fd4);                                                                                 // ...

        bzero(buffer,256);
        strcpy(buffer, "O[2]12.00,34.00|23.00,0.11");
        // fd5 = open(myfifo5,O_RDONLY);                                                               // Recive the obstacles position
        // if (fd5 == -1) {
        //     perror("Error opening FIFO5");
        // }
        // read(fd5, buffer, 255);
        // close(fd5);                                                                                 // ...
        n = write(sockfd,buffer,strlen(buffer));                                                    // Write the obstacles to server SOCKET

        // usleep(100);
        bzero(rbuffer,256);
        n = read(sockfd,rbuffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("bufferread3: %s  \n", rbuffer);





        // strcpy(buffer, "TI");
        // n = write(sockfd,buffer,strlen(buffer));
        // if (n < 0) 
        //     error("ERROR writing to socket");
        
        // bzero(rbuffer,256);
        // n = read(sockfd,rbuffer,255);
        // printf("bufferread1: %s  \n", buffer);
        // if (n < 0) 
        //     error("ERROR reading from socket");

        // bzero(rbuffer,256);
        // n = read(sockfd,rbuffer,255);
        // n = write(sockfd,rbuffer,strlen(rbuffer));
        // if (n < 0) 
        //     error("ERROR reading from socket");
        // printf("bufferread2: %s  \n", rbuffer);
        // fd7 = open(myfifo7,O_WRONLY);                                                               // Write window siza to goals
        // if (fd7 == -1) {
        //     perror("Error opening FIFO7");
        // }
        // write(fd7, rbuffer, 80);
        // close(fd7);                                                                                 // ...

        // bzero(buffer,256);
        // // strcpy(buffer, "O[2]12.00,34.00|23.00,0.11");
        // fd8 = open(myfifo8,O_RDONLY);                                                               // Recive the goals position
        // if (fd8 == -1) {
        //     perror("Error opening FIFO8");
        // }
        // read(fd8, buffer, 255);
        // close(fd8);                                                                                 // ...
        // n = write(sockfd,buffer,strlen(buffer));                                                    // Write the goals to server SOCKET

        // // usleep(100);
        // bzero(rbuffer,256);
        // n = read(sockfd,rbuffer,255);
        // if (n < 0) 
        //     error("ERROR reading from socket");
        // printf("bufferread3: %s  \n", rbuffer);

        // fd8 = open(myfifo8,O_WRONLY);                      // Send the obstacles position to force processor
        // if (fd8 == -1) {
        //     perror("Error opening FIFO8");
        // }
        // // sprintf(str8, format_string8, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        // write(fd8, buffer, strlen(buffer)+1);
        // close(fd8);

        // printf("%s\n",buffer);
        sleep(10);
    }
    // return 0;
}