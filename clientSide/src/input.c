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
    char str3[80];
    char format_string3[80]="%d,%f,%f,%f,%f";

    int fd4;
    char * myfifo4 = "/tmp/myfifo4";
    mkfifo(myfifo4, 0666);
    char str4[80];
    char format_string4[80]="%d,%d,%f,%f";

    int fd5;
    char * myfifo5 = "/tmp/myfifo5";
    mkfifo(myfifo5, 0666);
    char str5[160];
    char format_string5[160]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd10;
    char * myfifo10 = "/tmp/myfifo10";
    mkfifo(myfifo10, 0666);
    char str10[80];
    char format_string10[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

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
        read(fd3, str3, 80); 
        sscanf(str3, format_string3, &reachedAllTheGoals, &ee_x, &ee_y, &vx, &vy);
        close(fd2);

        if(reachedAllTheGoals || masterTerminate)
        {
            fd4 = open(myfifo4,O_WRONLY);               // Send the drone position to client processor (last dest: obstacle) and "masterTerminate" status
            if (fd4 == -1) {
                perror("Error opening FIFO4");
            }
            sprintf(str4, format_string4, masterTerminate, reachedAllTheGoals, ee_x, ee_y);
            write(fd4, str4, strlen(str4)+1);
            close(fd4);

            fd5 = open(myfifo5,O_RDONLY);       // Open fifo
            if (fd5 == -1) {                    // Error check
                perror("Error opening FIFO5");
            }
            read(fd5, str5, 160);                // Read from fifo
            sscanf(str5, format_string5, &ox1, &ox2, &ox3, &ox4, &ox5, &ox6, &ox7, &ox8, &ox9, &ox10, &oy1, &oy2, &oy3, &oy4, &oy5, &oy6, &oy7, &oy8, &oy9, &oy10, &gx1, &gx2, &gx3, &gx4, &gx5, &gx6, &gx7, &gx8, &gx9, &gx10, &gy1, &gy2, &gy3, &gy4, &gy5, &gy6, &gy7, &gy8, &gy9, &gy10);
            close(fd5);                         // Close the fifo
        }
        
        fd10 = open(myfifo10,O_RDONLY);
        if (fd10 == -1) {
            perror("Error opening FIFO10");
        }
        read(fd10, str10, 80);
        sscanf(str10, format_string10, &reachedGoal1, &reachedGoal2, &reachedGoal3, &reachedGoal4, &reachedGoal5, &reachedGoal6, &reachedGoal7, &reachedGoal8, &reachedGoal9, &reachedGoal10);
        close(fd10);

        // Update UI
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