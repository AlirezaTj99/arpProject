#include "./../include/master.h"

int main() {

    int fd1s; 
    char * myfifo1000s = "/tmp/myfifo1000s"; 
    mkfifo(myfifo1000s, 0666); 
    char str1s[80];
    char format_string1s[80]="%d";
    int masterTerminate = 0;

    int fd7; 
    char * myfifo7 = "/tmp/myfifo7"; 
    mkfifo(myfifo7, 0666); 
    char str7[80]; 
    char format_string7[80]="%d,%d";

    // Spawn obstacle Process
    char *arg_list_obstacle[] = {"/usr/bin/konsole", "-e", "./bin/obstacle", NULL};
    pid_t pid_obstacle = spawn("/usr/bin/konsole", arg_list_obstacle);

    // // Spawn goal Process
    // char *arg_list_goal[] = {"/usr/bin/konsole", "-e", "./bin/goal", NULL};
    // pid_t pid_goal = spawn("/usr/bin/konsole", arg_list_goal);

    // Spawn client Process
    char *arg_list_client[] = {"/usr/bin/konsole", "-e", "./bin/client 127.0.0.1 9005", NULL};
    pid_t pid_client = spawn("/usr/bin/konsole", arg_list_client);

    // Spawn Tclient Process
    char *arg_list_Tclient[] = {"/usr/bin/konsole", "-e", "./bin/Tclient 127.0.0.1 9005", NULL};
    pid_t pid_Tclient = spawn("/usr/bin/konsole", arg_list_Tclient);

    // fd7 = open(myfifo7,O_WRONLY);                      // Send the obstacles position to input processor
    // if (fd7 == -1) {
    //     perror("Error opening FIFO14");
    // }
    // sprintf(str7, format_string7, pid_obstacle, pid_goal);
    // write(fd7, str7, strlen(str7)+1);
    // close(fd7);

    // Infinite Loop
    while (1) {
        // fgets(masterTerminate, 80 , stdin); 
        fd1s = open(myfifo1000s,O_RDONLY); 
        if (fd1s == -1) {
            perror("Error opening FIFO1");
        }
        read(fd1s, str1s, 80); 
        // sscanf(str1s, format_string1s, &masterTerminate);
        close(fd1s);

        printf("Here is the message: masterTerminate=%s  \n", str1s);

        if (str1s[0]=='1') {
            usleep(20000);
            printf("Program terminate requested by CLIENT ....\nEntering kill process ...");
            // kill(pid_goal, SIGTERM);                                // Send the SIGTERM signal
            // kill(pid_obstacle, SIGTERM);
            kill(pid_client, SIGTERM);

            endwin();

            // Wait for the processes to finish
            int status_obstacle, status_goal, status_client;
            // waitpid(pid_goal, &status_goal, 0);
            // waitpid(pid_obstacle, &status_obstacle, 0);
            waitpid(pid_client, &status_client, 0);
            
            // Perform cleanup
            endwin();

            // Exit the program
            exit(0);
        }
    }

    return 0;
}

// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483