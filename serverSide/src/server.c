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

bool reachedAllTheGoals = 0;
int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;
int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10;
int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10;
float ee_x=0.0, ee_y=0.0;int masterTerminate = 0;
char format_buffer[160]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

void dostuff(int); /* function prototype */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{

    int sockfd, newsockfd, portno, clilen, pid;
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
    clilen = sizeof(cli_addr);
    while (1) {
        newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)  {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        }
        else close(newsockfd);
    } /* end of while */
    return 0; /* we never get here */
}

/******** DOSTUFF() *********************
There is a separate instance of this function 
for each connection.  It handles all communication
once a connnection has been established.
*****************************************/
void dostuff (int sock)
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

    int fd7s;
    char * myfifo7s = "/tmp/myfifo7s";
    mkfifo(myfifo7s, 0666);
    char str7s[80];
    char format_string7s[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd7; 
    char * myfifo7 = "/tmp/myfifo7"; 
    mkfifo(myfifo7, 0666); 
    char str7[80]; 
    char format_string7[80]="%d,%d";

    int n;
    char buffer[256];
    int pid_obstacle;
    int pid_goal;

    fd7 = open(myfifo7,O_RDONLY);                      // Send the obstacles position to input processor
    if (fd7 == -1) {
        perror("Error opening FIFO14");
    }
    read(fd7, str7, strlen(str7)+1);
    sscanf(str7, format_string7, &pid_obstacle, &pid_goal);
    close(fd7);
      
    bzero(buffer,256);
    n = read(sock,buffer,255);
    sscanf(buffer, format_string4, &masterTerminate, &reachedAllTheGoals, &ee_x, &ee_y);
    if (n < 0) error("ERROR reading from socket");

    if (ee_x==0.0 && ee_y ==0.0){
        masterTerminate = 1;
    }
    printf("Here is the message: masterTerminate=%d  <<<<<<======>>>>>>  ee_x=%f ...... ee_y=%f\n", masterTerminate, ee_x, ee_y);

    if (masterTerminate = 1)
    {
        kill(pid_goal, SIGTERM);                                // Send the SIGTERM signal
        kill(pid_obstacle, SIGTERM);
        endwin;
    }

    fd1s = open(myfifo1000s,O_WRONLY);            // send status to master
    if (fd4s == -1) {
        perror("Error opening FIFO4");
    }
    sprintf(str1s, format_string1s, masterTerminate, ee_x, ee_y);
    write(fd1s, str1s, strlen(str1s)+1); 
    close(fd1s); 
    printf("message: masterTerminate=%s  \n", str1s);

    fd4s = open(myfifo4s,O_WRONLY);               // Send the drone position to obstacle processor
    if (fd4s == -1) {
        perror("Error opening FIFO4");
    }
    sprintf(str4s, format_string4s, reachedAllTheGoals, ee_x, ee_y);
    write(fd4s, str4s, strlen(str4s)+1);
    close(fd4s);

    fd5s = open(myfifo5s,O_RDONLY);       // Open fifo
    if (fd5s == -1) {                    // Error check
        perror("Error opening FIFO5");
    }
    read(fd5s, str5s, 80);                // Read from fifo
    sscanf(str5s, format_string5s, &ox1, &ox2, &ox3, &ox4, &ox5, &ox6, &ox7, &ox8, &ox9, &ox10, &oy1, &oy2, &oy3, &oy4, &oy5, &oy6, &oy7, &oy8, &oy9, &oy10);
    close(fd5s); 

    fd7s = open(myfifo7s,O_RDONLY);
    if (fd7s == -1) {
        perror("Error opening FIFO7");
    }
    read(fd7s, str7s, 80);
    sscanf(str7s, format_string7s, &gx1, &gx2, &gx3, &gx4, &gx5, &gx6, &gx7, &gx8, &gx9, &gx10, &gy1, &gy2, &gy3, &gy4, &gy5, &gy6, &gy7, &gy8, &gy9, &gy10);
    close(fd7s);

    usleep(4000);

    bzero(buffer,256);
    sprintf(buffer, format_buffer, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10, gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10);
    n = write(sock,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
}