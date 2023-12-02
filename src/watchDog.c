#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct {
    volatile sig_atomic_t computation_in_progress;
} SHARED_DATA;

SHARED_DATA *shared_data;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        shared_data->computation_in_progress = 1;
    }
}

int main() {
    int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);}
    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    signal(SIGUSR1, signal_handler);

    pid_t inspection_pid, master_pid;

    while (1) {
        sleep(5);  // Adjust the sleep duration based on your requirements

        // Check if computation is in progress
        if (!shared_data->computation_in_progress) {
            // Notify or take action as needed
            printf("Watchdog: No computation in progress. Sending notification...\n");

            // Assuming inspection and master are the process names you want to monitor
            inspection_pid = fork();
            if (inspection_pid == 0) {
                execlp("/bin/ps", "ps", "ax", NULL);
                perror("execlp");
                exit(EXIT_FAILURE);
            }

            waitpid(inspection_pid, NULL, 0);

            master_pid = fork();
            if (master_pid == 0) {
                execlp("/bin/ps", "ps", "ax", NULL);
                perror("execlp");
                exit(EXIT_FAILURE);
            }

            waitpid(master_pid, NULL, 0);

            // Take any additional action or terminate the system
            printf("Watchdog: Taking action or stopping the system...\n");
            // Uncomment the line below if you want to stop the system
            // exit(EXIT_SUCCESS);
        } else {
            shared_data->computation_in_progress = 0;
        }
    }

    // Cleanup
    munmap(shared_data, sizeof(SHARED_DATA));
    close(shm_fd);

    return 0;
}