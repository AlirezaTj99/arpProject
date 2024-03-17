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

    bool reachedAllTheGoals = 1;

    while (TRUE)
    {
        fd7 = open(myfifo7,O_RDONLY);                                                               // Write window siza to obstacle
        if (fd7 == -1) {
            perror("Error opening FIFO7");
        }
        read(fd7, str7, sizeof(str7));
        sscanf(str7, format_string7, &max_x, &max_y);        // Import the deone co_ordinates
        close(fd7);
        if (reachedAllTheGoals)
        {
            spawn_random_g();                               // Spawn random goals
            reachedAllTheGoals = 0;
        }
        
        fd8 = open(myfifo8,O_WRONLY);                      // Send the obstacles position to SERVER processor
        if (fd8 == -1) {
            perror("Error opening FIFO8");
        }
        sprintf(str8, format_string8, gx1, gy1, gx2, gy2, gx3, gy3, gx4, gy4, gx5, gy5, gx6, gy6, gx7, gy7, gx8, gy8, gx9, gy9, gx10, gy10);
        write(fd8, str8, strlen(str8));
        close(fd8);
        printf("obstacle: %s  \n", str8);


        usleep(2000);
    }

    // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483