#include "./../include/inspection.h"

int main()
{
    int fd14; 
    char * myfifo14 = "/tmp/myfifo14"; 
    mkfifo(myfifo14, 0666); 
    char str14[80]; 
    char format_string14[80]="%d,%d,%d,%d"; 

    printf("Hi\nStarting my job ...\n");

    fd14 = open(myfifo14,O_RDONLY);       // Open fifo
    if (fd14 == -1) {                    // Error check
        perror("Error opening FIFO14");
    }
    read(fd14, str14, 80);                // Read from fifo
    sscanf(str14, format_string14, &pid_input, &pid_force, &pid_watchdog, &pid_client);
    close(fd14);  

    while(1)
    {
        printf("The pid_input: %d, pid_force: %d, pid_watchdog:%d, pid_client:%d\n",pid_input, pid_force, pid_watchdog, pid_client);
        usleep(300000);

        if (kill(pid_input, 0) == -1) {
            // Check the specific error
            if (errno == ESRCH) {
                // No such process
                printf("Input process (PID: %d) is stopped or does not exist.\n", pid_input);
                inputIsRunning = 0;
            } else if (errno == EPERM) {
                // Process exists but we don't have permission to send a signal
                printf("Input process (PID: %d) is running, but no permission to check.\n", pid_input);
                inputIsRunning = 1;
            } else {
                // Some other error
                printf("Failed to check status of input process (PID: %d): %s\n", pid_input, strerror(errno));
            }
        } else {
            // Process exists and we can send a signal, so it's running
            printf("Input process (PID: %d) is running.\n", pid_input);
            inputIsRunning = 1;
            }
        usleep(300000);

        if (inputIsRunning)
        {
            if (kill(pid_force, 0) == -1) {
                // Check the specific error
                if (errno == ESRCH) {
                    // No such process
                    printf("Force process (PID: %d) is stopped or does not exist.\n", pid_force);
                    forceIsRunning = 0;
                } else if (errno == EPERM) {
                    // Process exists but we don't have permission to send a signal
                    printf("Force process (PID: %d) is running, but no permission to check.\n", pid_force);
                    forceIsRunning = 1;
                } else {
                    // Some other error
                    printf("Failed to check status of force process (PID: %d): %s\n", pid_force, strerror(errno));
                }
            } else {
                // Process exists and we can send a signal, so it's running
                printf("Force process (PID: %d) is running.\n", pid_force);
                forceIsRunning = 1;
                }
            usleep(300000);

            if (forceIsRunning)
            {
                if (kill(pid_watchdog, 0) == -1) {
                    // Check the specific error
                    if (errno == ESRCH) {
                        // No such process
                        printf("Watchdog process (PID: %d) is stopped or does not exist.\n", pid_watchdog);
                        watchdogIsRunning = 0;
                    } else if (errno == EPERM) {
                        // Process exists but we don't have permission to send a signal
                        printf("Watchdog process (PID: %d) is running, but no permission to check.\n", pid_watchdog);
                        watchdogIsRunning = 1;
                    } else {
                        // Some other error
                        printf("Failed to check status of watchdog process (PID: %d): %s\n", pid_watchdog, strerror(errno));
                    }
                } else {
                    // Process exists and we can send a signal, so it's running
                    printf("Watchdog process (PID: %d) is running.\n", pid_watchdog);
                    watchdogIsRunning = 1;
                    }
                usleep(300000);

                if (watchdogIsRunning)
                {
                    if (kill(pid_client, 0) == -1) {
                        // Check the specific error
                        if (errno == ESRCH) {
                            // No such process
                            printf("client process (PID: %d) is stopped or does not exist.\n", pid_client);
                            clientIsRunning = 0;
                        } else if (errno == EPERM) {
                            // Process exists but we don't have permission to send a signal
                            printf("client process (PID: %d) is running, but no permission to check.\n", pid_client);
                            clientIsRunning = 1;
                        } else {
                            // Some other error
                            printf("Failed to check status of client process (PID: %d): %s\n", pid_client, strerror(errno));
                        }
                    } else {
                        // Process exists and we can send a signal, so it's running
                        printf("client process (PID: %d) is running.\n", pid_client);
                        clientIsRunning = 1;
                        }
                    usleep(300000);

                }
            }
        }
    }
}

// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483