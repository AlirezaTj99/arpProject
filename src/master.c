#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include "./../include/inspection_utilities.h"

int spawn(const char *program, char *arg_list[]) {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Error while forking...");
        return 1;
    } else if (child_pid != 0) {
        return child_pid;
    } else {
        if (execvp(program, arg_list) == 0) {
            perror("Exec failed");
            return 1;
        }
    }
}

void cleanup() {
    endwin();
    munmap(shared_data, sizeof(SHARED_DATA));
    shm_unlink("/my_shared_memory");
}

void handle_signal(int signum) {
    // Handle signals (if needed)
    cleanup();
    exit(EXIT_SUCCESS);
}

int main() {
    // Set up signal handling
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Initialize Shared Memory
    int shm_fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize User Interface
    init_console_ui();

    // Spawn Inspection Console Process
    char *arg_list_inspection[] = {"/usr/bin/konsole", "-e", "./bin/inspection", NULL};
    pid_t pid_inspection = spawn("/usr/bin/konsole", arg_list_inspection);

    // Spawn Watchdog Process
    char *arg_list_watchdog[] = {"/usr/bin/konsole", "-e", "./bin/watchdog", NULL};
    pid_t pid_watchdog = spawn("/usr/bin/konsole", arg_list_watchdog);

    // Infinite Loop
    while (1) {
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();

        // Rest of your code handling UI and updating shared data

        // Update UI
        update_console_ui(&shared_data->ee_x, &shared_data->ee_y, &shared_data->vx, &shared_data->vy, blackboard);
    }

    // Cleanup
    cleanup();

    // Wait for the processes to finish
    int status_inspection, status_watchdog;
    waitpid(pid_inspection, &status_inspection, 0);
    waitpid(pid_watchdog, &status_watchdog, 0);

    return 0;
}