#include "./../include/obstacle.h"

int main()
{
    int fd4;
    char * myfifo4 = "/tmp/myfifo4";
    mkfifo(myfifo4, 0666);
    char str4[80];
    char format_string4[80]="%f,%f";

    int fd5;
    char * myfifo5 = "/tmp/myfifo5";
    mkfifo(myfifo5, 0666);
    char str5[80];
    char format_string5[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd6;
    char * myfifo6 = "/tmp/myfifo6";
    mkfifo(myfifo6, 0666);
    char str6[80];
    char format_string6[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd8;
    char * myfifo8 = "/tmp/myfifo8";
    mkfifo(myfifo8, 0666);
    char str8[80];
    char format_string8[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd11; 
    char * myfifo11 = "/tmp/myfifo11"; 
    mkfifo(myfifo11, 0666); 
    char str11[80]; 
    char format_string11[80]="%d";
    
    bool reachedAllTheGoals = 1;

    while (TRUE)
    {

        fd4 = open(myfifo4,O_RDONLY);
        if (fd4 == -1) {
            perror("Error opening FIFO4");
        }
        read(fd4, str4, 80);
        sscanf(str4, format_string4, &ee_x, &ee_y);        // Import the deone co_ordinates
        if(reachedAllTheGoals)                             // Check if the drone reached all the goals
        {
            spawn_random_o();                              // Spawn random obstacles
        }
        close(fd4);

        fd5 = open(myfifo5,O_WRONLY);                      // Send the obstacles position to input processor
        if (fd5 == -1) {
            perror("Error opening FIFO5");
        }
        sprintf(str5, format_string5, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd5, str5, strlen(str5)+1);
        close(fd5);

        fd6 = open(myfifo6,O_WRONLY);                      // Send the obstacles position to goal processor
        if (fd6 == -1) {
            perror("Error opening FIFO6");
        }
        sprintf(str6, format_string6, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd6, str6, strlen(str6)+1);
        close(fd6);

        fd8 = open(myfifo8,O_WRONLY);                      // Send the obstacles position to force processor
        if (fd8 == -1) {
            perror("Error opening FIFO8");
        }
        sprintf(str8, format_string8, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd8, str8, strlen(str8)+1);
        close(fd8);

        fd11 = open(myfifo11,O_RDONLY);
        if (fd11 == -1) {
            perror("Error opening FIFO11");
        }
        read(fd11, str11, 80);
        sscanf(str11, format_string11, &reachedAllTheGoals);  // Updates to check if the drone reached all the goals
        close(fd11);
        usleep(2000);

        //     spawn_random_o();
        //     shared_data->reachedAllTheGoals = 0;
        //     usleep(10);
        //     shared_data->allowGoalSpawn = 1;
        //     usleep(10);
        // }
    }

    // // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483