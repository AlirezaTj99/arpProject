#include "./../include/obstacle.h"

int main()
{
    int fd4s;
    char * myfifo4s = "/tmp/myfifo4s";
    mkfifo(myfifo4s, 0666);
    char str4s[80];
    char format_string4s[80]="%d,%f,%f";

    int fd5s;
    char * myfifo5s = "/tmp/myfifo5s";
    mkfifo(myfifo5s, 0666);
    char str5s[80];
    char format_string5s[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd6s;
    char * myfifo6s = "/tmp/myfifo6s";
    mkfifo(myfifo6s, 0666);
    char str6s[80];
    char format_string6s[100]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";
    
    bool reachedAllTheGoals = 0;

    while (TRUE)
    {

        fd4s = open(myfifo4s,O_RDONLY);
        if (fd4s == -1) {
            perror("Error opening FIFO4");
        }
        read(fd4s, str4s, 80);
        sscanf(str4s, format_string4s, &reachedAllTheGoals, &ee_x, &ee_y);        // Import the deone co_ordinates
        if(reachedAllTheGoals)                             // Check if the drone reached all the goals
        {
            spawn_random_o();                              // Spawn random obstacles
            // reachedAllTheGoals = 0;
        }
        close(fd4s);

        fd5s = open(myfifo5s,O_WRONLY);                      // Send the obstacles position to SERVER processor
        if (fd5s == -1) {
            perror("Error opening FIFO5");
        }
        sprintf(str5s, format_string5s, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd5s, str5s, strlen(str5s)+1);
        close(fd5s);

        fd6s = open(myfifo6s,O_WRONLY);                      // Send the obstacles position to goal processor
        if (fd6s == -1) {
            perror("Error opening FIFO6");
        }
        sprintf(str6s, format_string6s, reachedAllTheGoals, ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
        write(fd6s, str6s, strlen(str6s)+1);
        close(fd6s);

        usleep(2000);

    }

    // // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483