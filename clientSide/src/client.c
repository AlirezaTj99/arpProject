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
    char format_string4[80]="%d,%f,%f";

    int fd5;
    char * myfifo5 = "/tmp/myfifo5";
    mkfifo(myfifo5, 0666);

    int fd8;
    char * myfifo8 = "/tmp/myfifo8";
    mkfifo(myfifo8, 0666);
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
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

            fd4 = open(myfifo4,O_RDONLY);
            if (fd4 == -1) {
                perror("Error opening FIFO4");
            }
            read(fd4, buffer, 80);
            sscanf(buffer, format_string4, &masterTerminate, &reachedAllTheGoals, &ee_x, &ee_y);        // Import the deone co_ordinates
            close(fd4);

        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
            error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        // sscanf(buffer, format_buffer, &ox1, &ox2, &ox3, &ox4, &ox5, &ox6, &ox7, &ox8, &ox9, &ox10, &oy1, &oy2, &oy3, &oy4, &oy5, &oy6, &oy7, &oy8, &oy9, &oy10, &gx1, &gx2, &gx3, &gx4, &gx5, &gx6, &gx7, &gx8, &gx9, &gx10, &gy1, &gy2, &gy3, &gy4, &gy5, &gy6, &gy7, &gy8, &gy9, &gy10);
        
        fd5 = open(myfifo5,O_WRONLY);                      // Send the obstacles position to input processor
        if (fd5 == -1) {
            perror("Error opening FIFO5");
        }
        // sprintf(str5, format_string5, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd5, buffer, strlen(buffer)+1);
        close(fd5);

        fd8 = open(myfifo8,O_WRONLY);                      // Send the obstacles position to force processor
        if (fd8 == -1) {
            perror("Error opening FIFO8");
        }
        // sprintf(str8, format_string8, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd8, buffer, strlen(buffer)+1);
        close(fd8);

        // printf("%s\n",buffer);
    }
    // return 0;
}