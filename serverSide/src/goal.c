#include "./../include/goal.h"

int main()
{
    int fd6s;
    char * myfifo6s = "/tmp/myfifo6s";
    mkfifo(myfifo6s, 0666);
    char str6s[80];
    char format_string6s[100]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd7s;
    char * myfifo7s = "/tmp/myfifo7s";
    mkfifo(myfifo7s, 0666);
    char str7s[80];
    char format_string7s[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    bool reachedAllTheGoals = 1;

    while (TRUE)
    {
        fd6s = open(myfifo6s,O_RDONLY);                   // Import the obstackes co-ordinates
        if (fd6s == -1) {
            perror("Error opening FIFO6");
        }
        read(fd6s, str6s, 80);
        sscanf(str6s, format_string6s, &reachedAllTheGoals, &ox1, &ox2, &ox3, &ox4, &ox5, &ox6, &ox7, &ox8, &ox9, &ox10, &oy1, &oy2, &oy3, &oy4, &oy5, &oy6, &oy7, &oy8, &oy9, &oy10);
        close(fd6s);
        if(reachedAllTheGoals)                            // Check if drone reached all goals
        {
            spawn_random_g();                               // Spawn random goals
            // reachedAllTheGoals = 0;
        }
        
        fd7s = open(myfifo7s,O_WRONLY);                      // Send the goals position to SERVER processor
        if (fd7s == -1) {
            perror("Error opening FIFO7");
        }
        sprintf(str7s, format_string7s, gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10);
        write(fd7s, str7s, strlen(str7s)+1);
        close(fd7s);

        usleep(2000);
    }

    // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483