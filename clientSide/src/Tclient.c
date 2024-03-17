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

    char buffer[1024];
    char rbuffer[1024];

    
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
        bzero(buffer,sizeof(rbuffer));


        strcpy(buffer, "OI");
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
            error("ERROR writing to socket");

        bzero(rbuffer,sizeof(rbuffer));
        // usleep(100);
        n = read(sockfd,rbuffer,sizeof(rbuffer));
        usleep(100);
        printf("readIO Feedback: %s  \n", buffer);
        if (n < 0) 
            error("ERROR reading from socket");
        //........................................................................................................................................................
        bzero(rbuffer,sizeof(rbuffer));
        n = read(sockfd,rbuffer,sizeof(rbuffer));
        printf("readWindowSize: %s  \n", rbuffer);
        n = write(sockfd,rbuffer,strlen(rbuffer));
        if (n < 0) 
            error("ERROR reading from socket");
        usleep(100);
        fd4 = open(myfifo4,O_WRONLY);                                                               // Write window siza to obstacle
        if (fd4 == -1) {
            perror("Error opening FIFO4");
        }
        write(fd4, rbuffer, strlen(rbuffer));
        close(fd4);                                                                                 // ...

        bzero(rbuffer,sizeof(rbuffer));
        bzero(buffer,sizeof(rbuffer));
        strcpy(buffer, "O[10]12.00,20.00|23.00,11.00|56.00,5.00|98.00,13.00|31.00,24.00|46.00,21.00|75.00,2.00|38.00,16.00|42.00,23.00|19.00,14.00");
        fd5 = open(myfifo5,O_RDONLY);                                                               // Recive the obstacles position
        if (fd5 == -1) {
            perror("Error opening FIFO5");
        }
        read(fd5, buffer, sizeof(buffer));
        close(fd5);                                                                                 // ...
        //.......................................................................................................................................................
        n = write(sockfd,buffer,strlen(buffer));                                                    // Write the obstacles to server SOCKET

        usleep(10000);
        n = read(sockfd,rbuffer,sizeof(rbuffer));
        if (n < 0) 
            error("ERROR reading from socket");
        printf("readObstacleEcho: %s  \n", rbuffer);

        sleep(10);
    }
    return 0;
}