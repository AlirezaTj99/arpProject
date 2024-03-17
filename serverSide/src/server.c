/* A simple server in the internet domain using TCP
   The port number is passed as an argument 
   This version runs forever, forking off a separate 
   process for each connection
   gcc server2.c -lsocket
*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>

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

#include <sys/shm.h>
#include <semaphore.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <bits/sigaction.h>

bool reachedAllTheGoals = 0;
int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;
int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10;
int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10;
float ee_x=0.0, ee_y=0.0;int masterTerminate = 0;
char format_buffer[160]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int fd1s; 
    char * myfifo1000s = "/tmp/myfifo1000s"; 
    mkfifo(myfifo1000s, 0666);
    char str1s[80]; 
    char format_string1s[80]="%d,%f,%f";

    int fd4s;
    char * myfifo4s = "/tmp/myfifo4s";
    mkfifo(myfifo4s, 0666);
    char str4s[80];
    char format_string4[80]="%d,%d,%f,%f";
    char format_string4s[80]="%d,%f,%f";

    int fd5s;
    char * myfifo5s = "/tmp/myfifo5s";
    mkfifo(myfifo5s, 0666);
    char str5s[80];
    char format_string5s[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd6;
    char * myfifo6 = "/tmp/myfifo6";
    mkfifo(myfifo6, 0666);

    // int fd7; 
    // char * myfifo7 = "/tmp/myfifo7"; 
    // mkfifo(myfifo7, 0666); 
    // char str7[80]; 
    // char format_string7[80]="%d,%d";

    int fd9;
    char * myfifo9 = "/tmp/myfifo9";
    mkfifo(myfifo9, 0666);

    int n;
    int pid_obstacle;
    int pid_goal;

    int sockfd, newsockfd, sock, portno, clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
            error("ERROR on binding");
    listen(sockfd,5);
    while (1) 
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        bzero(buffer,sizeof(buffer));
        n = read(newsockfd,buffer,sizeof(buffer));
        if (n < 0) error("ERROR reading from socket");


        printf("buffer1: %s  \n", buffer);
        n = write(newsockfd,buffer,strlen(buffer));
        //......................................................................................................................
        bzero(buffer,sizeof(buffer));
        usleep(10000);
        strcpy(buffer, "101.000,41.000");
        n = write(newsockfd,buffer,strlen(buffer));
        // usleep(100);

        bzero(buffer,sizeof(buffer));
        n = read(newsockfd,buffer,sizeof(buffer));
        if (n < 0) error("ERROR reading from socket");
        printf("readWindowSizeEcho: %s  \n", buffer);
        bzero(buffer,sizeof(buffer));
        usleep(10000);
        n = read(newsockfd,buffer,sizeof(buffer));
        if (n < 0) error("ERROR reading from socket");
        printf("readObstacle/Target: %s  \n", buffer);

        n = write(newsockfd,buffer,strlen(buffer));
        fd6 = open(myfifo6,O_WRONLY);
        if (fd6 == -1) {
            perror("Error opening FIFO7");
        }
        write(fd6, buffer, strlen(buffer)+1);
        close(fd6);
        printf("write is done  \n");

    }
    close(sockfd);
    return 0; 
}