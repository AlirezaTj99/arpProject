#include "./../include/master.h"

int main() {

    int fd1; 
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
    char masterTerminate[80];

    int fd14; 
    char * myfifo14 = "/tmp/myfifo14"; 
    mkfifo(myfifo14, 0666); 
    char str14[80]; 
    char format_string14[80]="%d,%d,%d,%d,%d"; 

    // Spawn input Process
    char *arg_list_input[] = {"/usr/bin/konsole", "-e", "./bin/input", NULL};
    pid_t pid_input = spawn("/usr/bin/konsole", arg_list_input);

    // Spawn force Process
    char *arg_list_force[] = {"/usr/bin/konsole", "-e", "./bin/force", NULL};
    pid_t pid_force = spawn("/usr/bin/konsole", arg_list_force);

    // Spawn obstacle Process
    char *arg_list_obstacle[] = {"/usr/bin/konsole", "-e", "./bin/obstacle", NULL};
    pid_t pid_obstacle = spawn("/usr/bin/konsole", arg_list_obstacle);

    // Spawn goal Process
    char *arg_list_goal[] = {"/usr/bin/konsole", "-e", "./bin/goal", NULL};
    pid_t pid_goal = spawn("/usr/bin/konsole", arg_list_goal);

    // Spawn Watchdog Process
    char *arg_list_watchdog[] = {"/usr/bin/konsole", "-e", "./bin/watchdog", NULL};
    pid_t pid_watchdog = spawn("/usr/bin/konsole", arg_list_watchdog);

    // Spawn inspection Process
    char *arg_list_inspection[] = {"/usr/bin/konsole", "-e", "./bin/inspection", NULL};
    pid_t pid_inspection = spawn("/usr/bin/konsole", arg_list_inspection);

    fd14 = open(myfifo14,O_WRONLY);                      // Send the obstacles position to input processor
    if (fd14 == -1) {
        perror("Error opening FIFO14");
    }
    sprintf(str14, format_string14, pid_input, pid_force, pid_obstacle, pid_goal, pid_watchdog);
    write(fd14, str14, strlen(str14)+1);
    close(fd14);

    // Infinite Loop
    while (1) {
        // fgets(masterTerminate, 80 , stdin); 
        fd1 = open(myfifo,O_RDONLY); 
        if (fd1 == -1) {
            perror("Error opening FIFO1");
        }
        read(fd1, masterTerminate, 80); 
        // sscanf(str1, format_string, &masterTerminate);
        close(fd1);

        if (masterTerminate[0]=='1') {
            kill(pid_goal, SIGTERM);  // Send the SIGTERM signal
            kill(pid_force, SIGTERM);
            kill(pid_input, SIGTERM);
            kill(pid_obstacle, SIGTERM);
            kill(pid_watchdog, SIGTERM);
            
            // Perform cleanup
            endwin();

            // Wait for the processes to finish
            int status_input, status_force, status_obstacle, status_goal, status_watchdog;
            waitpid(pid_goal, &status_goal, 0);
            waitpid(pid_input, &status_input, 0);
            waitpid(pid_force, &status_force, 0);
            waitpid(pid_obstacle, &status_obstacle, 0);
            waitpid(pid_watchdog, &status_watchdog, 0);

            // Exit the program
            exit(0);
        }
        sleep(1);

        // Update UI
        // update_console_ui(&shared_data->ee_x, &shared_data->ee_y, &shared_data->vx, &shared_data->vy, blackboard);
    }

    return 0;
}

// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483