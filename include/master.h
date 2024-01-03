// #ifndef MASTER_H
#define MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

// Include other necessary modules
// #include "court.h"
// #include "drone.h"
#include "input.h"

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