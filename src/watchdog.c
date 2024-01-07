#include "./../include/watchdog.h"

int main() {

    int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // signal(SIGUSR1, signal_handler);

    pid_t pid_input, master_pid;

    while (1) {
        sleep(1);  
        int c1=shared_data->computation_in_progress;
        int c2=no_computation_count;
        
        // Check if computation is in progress
        if (shared_data->computation_in_progress ) {
            // Notify or take action as needed

            no_computation_count = 1;
            printf("computation_in_progress output = %d ===>>> Watchdog: Good condition...\n",c1);

            // // input and master are the process names we want to monitor
            // pid_input = fork();
            // if (pid_input == 0) {
            //     execlp("/bin/ps", "ps", "ax", NULL);
            //     perror("execlp");
            //     exit(EXIT_FAILURE);
            // }

            // waitpid(pid_input, NULL, 0);

            // master_pid = fork();
            // if (master_pid == 0) {
            //     execlp("/bin/ps", "ps", "ax", NULL);
            //     perror("execlp");
            //     exit(EXIT_FAILURE);
            // }

            // waitpid(master_pid, NULL, 0);

            // // Take any additional action or terminate the system
            // printf("Watchdog: 1111Taking action or stopping the system...\n");
            // // Uncomment the line below if you want to stop the system
            // exit(EXIT_SUCCESS);
            // shared_data->close_master = 1;  // Signal to master to close

        }
        else {

            printf("computation_in_progress output = %d, no_computation_count = %d ===>>> Watchdog: No computation in progress. Sending notification...\n",c1,c2);

            no_computation_count++;

            if (no_computation_count > 25) {
                // No computation is ongoing for the specified timeout duration; take action
                printf("No computation is ongoing for %d seconds! Stopping the system...\n",c2);
                sleep(10);
                shared_data->close_master = 1;  // Signal to master to close
                exit(EXIT_FAILURE);
            }
        }
    }

    // Cleanup
    cleanup();

    return 0;
}