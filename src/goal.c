#include "./../include/goal.h"

int main()
{
    int fd6;
    char * myfifo6 = "/tmp/myfifo6";
    mkfifo(myfifo6, 0666);
    char str6[80];
    char format_string6[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd7;
    char * myfifo7 = "/tmp/myfifo7";
    mkfifo(myfifo7, 0666);
    char str7[80];
    char format_string7[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd9;
    char * myfifo9 = "/tmp/myfifo9";
    mkfifo(myfifo9, 0666);
    char str9[80];
    char format_string9[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd12; 
    char * myfifo12 = "/tmp/myfifo12"; 
    mkfifo(myfifo12, 0666); 
    char str12[80]; 
    char format_string12[80]="%d";

    int fd14; 
    char * myfifo14 = "/tmp/myfifo14"; 
    mkfifo(myfifo14, 0666); 
    char str14[80]; 
    char format_string14[80]="%d";
    bool goalTerminate = 0;

    bool reachedAllTheGoals = 1;
    
    // Initialize Shared Memory
    // int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
    // if (shm_fd == -1) {
    //     perror("shm_open");
    //     exit(EXIT_FAILURE);
    // }
    // ftruncate(shm_fd, sizeof(SHARED_DATA));
    // shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // shared_data->reachedAllTheGoals = 1;

    while (TRUE)
    {
        fd6 = open(myfifo6,O_RDONLY);                   // Import the obstackes co-ordinates
        if (fd6 == -1) {
            perror("Error opening FIFO6");
        }
        read(fd6, str6, 80);
        sscanf(str6, format_string6, &ox1, &ox2, &ox3, &ox4, &ox5, &ox6, &ox7, &ox8, &ox9, &ox10, &oy1, &oy2, &oy3, &oy4, &oy5, &oy6, &oy7, &oy8, &oy9, &oy10);
        close(fd6);
        if(reachedAllTheGoals)                            // Check if drone reached all goals
        {
            // shared_data->reachedGoal1 = 0;
            // shared_data->reachedGoal2 = 0;
            // shared_data->reachedGoal3 = 0;
            // shared_data->reachedGoal4 = 0;
            // shared_data->reachedGoal5 = 0;
            // shared_data->reachedGoal6 = 0;
            // shared_data->reachedGoal7 = 0;
            // shared_data->reachedGoal8 = 0;
            // shared_data->reachedGoal9 = 0;
            // shared_data->reachedGoal10 = 0;
            // importObstacleCoordinates();
            spawn_random_g();                               // Spawn random goals
            // shared_data->allowGoalSpawn = 0;
        }
        
        fd7 = open(myfifo7,O_WRONLY);                      // Send the goals position to input processor
        if (fd7 == -1) {
            perror("Error opening FIFO7");
        }
        sprintf(str7, format_string7, gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10);
        write(fd7, str7, strlen(str7)+1);
        close(fd7);

        fd9 = open(myfifo9,O_WRONLY);                      // Send the goals position to force processor
        if (fd9 == -1) {
            perror("Error opening FIFO9");
        }
        sprintf(str9, format_string9, gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10);
        write(fd9, str9, strlen(str9)+1);
        close(fd9);

        fd12 = open(myfifo12,O_RDONLY);                     // Updates to check if the drone reached all the goals
        if (fd12 == -1) {
            perror("Error opening FIFO12");
        }
        read(fd12, str12, 80);
        sscanf(str12, format_string12, &reachedAllTheGoals);
        close(fd12);
        usleep(2000);
    }

    // Cleanup
    endwin();

    return 0;
}
// 0.002000



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483