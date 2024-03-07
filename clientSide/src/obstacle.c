#include "./../include/obstacle.h"

int main()
{
    // int fd4s;
    // char * myfifo4s = "/tmp/myfifo4s";
    // mkfifo(myfifo4s, 0666);
    // char str4s[80];
    // char format_string4s[80]="%d,%f,%f";

    int fd4;
    char * myfifo4 = "/tmp/myfifo4";
    mkfifo(myfifo4, 0666);
    char str4[80];
    char format_string4[80]="%d,%d";

    int fd5;
    char * myfifo5 = "/tmp/myfifo5";
    mkfifo(myfifo5, 0666);
    char str5[128];
    char format_string5[128]="O[10]%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00";

    // int fd6s;
    // char * myfifo6s = "/tmp/myfifo6s";
    // mkfifo(myfifo6s, 0666);
    // char str6s[80];
    // char format_string6s[100]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
    
    bool reachedAllTheGoals = 0;

    while (TRUE)
    {
        fd4 = open(myfifo4,O_RDONLY);
        if (fd4 == -1) {
            perror("Error opening FIFO4");
        }
        read(fd4, str4, 80);
        sscanf(str4, format_string4, &max_x, &max_y);        // Import the deone co_ordinates
        close(fd4);
        spawn_random_o();                              // Spawn random obstacles
            // reachedAllTheGoals = 0;
        // }
        // close(fd4s);

        fd5 = open(myfifo5,O_WRONLY);                      // Send the obstacles position to SERVER processor
        if (fd5 == -1) {
            perror("Error opening FIFO5");
        }
        sprintf(str5, format_string5, ox1, oy1, ox2, oy2, ox3, oy3, ox4, oy4, ox5, oy5, ox6, oy6, ox7, oy7, ox8, oy8, ox9, oy9, ox10, oy10);
        write(fd5, str5, strlen(str5)+1);
        close(fd5);
        printf("obstacle: %s  \n", str5);

        // fd6s = open(myfifo6s,O_WRONLY);                      // Send the obstacles position to goal processor
        // if (fd6s == -1) {
        //     perror("Error opening FIFO6");
        // }
        // sprintf(str6s, format_string6s, reachedAllTheGoals, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        // write(fd6s, str6s, strlen(str6s)+1);
        // close(fd6s);

        usleep(2000);

    }

    // // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483