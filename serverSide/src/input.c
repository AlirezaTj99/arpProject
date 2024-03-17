#include "./../include/input.h"

int main()
{
    initscr(); // Initialize the window
    cbreak();  // Line buffering disabled
    noecho();  // Don't echo while we do getch

    int fd1; 
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
    char str1[80]; 
    char format_string[80]="%d";
    bool masterTerminate = 0;

    int fd2; 
    char * myfifo2 = "/tmp/myfifo2"; 
    mkfifo(myfifo2, 0666); 
    char str2[80]; 
    char format_string2[80]="%d";
    int keySignal = 0;

    int fd3;
    char * myfifo3 = "/tmp/myfifo3";
    mkfifo(myfifo3, 0666);
    char str3[1024];
    char format_string3[1024]="[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d]%d,%f,%f,%f,%f[%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f][%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f]";

    int fd6;
    char * myfifo6 = "/tmp/myfifo6";
    mkfifo(myfifo6, 0666);
    char str6[1024];
    char format_string6[1024]="O[10]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";

    int fd9;
    char * myfifo9 = "/tmp/myfifo9";
    mkfifo(myfifo9, 0666);
    char str9[1024];
    char format_string9[1024]="T[10]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";

    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;

    // End-effector coordinates
    float ee_x = 0.0, ee_y = 0.0;

    // Defining the velocities
    float vx = 0.0;
    float vy = 0.0;

    bool reachedAllTheGoals = 0;

    // Initialize User Interface 
    init_console_ui();

    // Infinite loop
    while(TRUE)
    {  
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();
        usleep(1000);

        // If user resizes screen, re-draw UI
        if(cmd == KEY_RESIZE || cmd == KEY_EVENT) 
        {
            reset_console_ui();
            reset_console_ui();
        }
        usleep(1000);

        // The key commands ...
        switch (cmd)
        {
            // for each key press we apply a 1N force for 1 second, and send the signal to shared data.
            case '7':
                keySignal = 7;
                break;
            case '9':
                keySignal = 9;
                break;
            case '1':
                keySignal = 1;
                break;
            case '3':
                keySignal = 3;
                break;
            case '4':
                keySignal = 4;
                break;
            case '6':
                keySignal = 6;
                break;
            case '8':
                keySignal = 8;
                break;
            case '2':
                keySignal = 2;
                break;
            case '5':
                keySignal = 5;
                break;
            case 'q':
                masterTerminate = 1;
                break;
            default:
                keySignal = 0;
                break;
        } 
        fd1 = open(myfifo,O_WRONLY);    // Open fifo
        sprintf(str1, format_string, masterTerminate);
        write(fd1, str1, strlen(str1)+1); 
        close(fd1); 

        fd2 = open(myfifo2,O_WRONLY); 
        if (fd2 == -1) {
            perror("Error opening FIFO2");
        }
        sprintf(str2, format_string2, keySignal);
        write(fd2, str2, strlen(str2)+1);
        close(fd2);
        usleep(1000);

        fd3 = open(myfifo3,O_RDONLY);
        if (fd3 == -1) {
            perror("Error opening FIFO3");
        }
        read(fd3, str3, sizeof(str3)); 
        sscanf(str3, format_string3, &reachedGoal1, &reachedGoal2, &reachedGoal3, &reachedGoal4, &reachedGoal5, &reachedGoal6, &reachedGoal7, &reachedGoal8, &reachedGoal9, &reachedGoal10, &reachedAllTheGoals, &ee_x, &ee_y, &vx, &vy, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10);
        close(fd3);

        update_console_ui(&ee_x, &ee_y, &vx, &vy);

        usleep(1000);
    }

    // Cleanup
    endwin();

    return 0;
}
// 0.006000


// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483