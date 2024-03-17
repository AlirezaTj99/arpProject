#include "./../include/goal.h"

int main()
{
    int fd7;
    char * myfifo7 = "/tmp/myfifo7";
    mkfifo(myfifo7, 0666);
    char str7[80];
    char format_string7[80]="%d,%d";

    int fd8;
    char * myfifo8 = "/tmp/myfifo8";
    mkfifo(myfifo8, 0666);
    char str8[128];
    char format_string8[128]="T[10]%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00|%d.00,%d.00";

    // int fd6s;
    // char * myfifo6s = "/tmp/myfifo6s";
    // mkfifo(myfifo6s, 0666);
    // char str6s[80];
    // char format_string6s[100]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    // int fd7s;
    // char * myfifo7s = "/tmp/myfifo7s";
    // mkfifo(myfifo7s, 0666);
    // char str7s[80];
    // char format_string7s[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    bool reachedAllTheGoals = 1;

    while (TRUE)
    {
        fd7 = open(myfifo7,O_RDONLY);                                                               // Write window siza to obstacle
        if (fd7 == -1) {
            perror("Error opening FIFO7");
        }
        read(fd7, str7, 80);
        sscanf(str7, format_string7, &max_x, &max_y);        // Import the deone co_ordinates
        close(fd7);
        
        spawn_random_g();                               // Spawn random goals
        
        fd8 = open(myfifo8,O_WRONLY);                      // Send the obstacles position to SERVER processor
        if (fd8 == -1) {
            perror("Error opening FIFO8");
        }
        sprintf(str8, format_string8, gx1, gy1, gx2, gy2, gx3, gy3, gx4, gy4, gx5, gy5, gx6, gy6, gx7, gy7, gx8, gy8, gx9, gy9, gx10, gy10);
        write(fd8, str8, strlen(str8)+1);
        close(fd8);
        printf("obstacle: %s  \n", str8);




        // fd7s = open(myfifo7s,O_WRONLY);                      // Send the goals position to SERVER processor
        // if (fd7s == -1) {
        //     perror("Error opening FIFO7");
        // }
        // sprintf(str7s, format_string7s, gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10);
        // write(fd7s, str7s, strlen(str7s)+1);
        // close(fd7s);

        usleep(2000);
    }

    // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483