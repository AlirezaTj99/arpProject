// #ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>   // For signaling related operations
#include <unistd.h>   // For sleep
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#include "./court.h"


// typedef struct {
//     volatile sig_atomic_t computation_in_progress;
//     volatile sig_atomic_t close_master;
// } SHARED_DATA;

// SHARED_DATA *shared_data;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        shared_data->computation_in_progress = 1;
    }
}

void cleanup() {
    munmap(shared_data, sizeof(SHARED_DATA));
    shm_unlink("/my_shared_memory");
}

int no_computation_count = 1;

// void handle_signal(int signum) {
//     // Handle signals (if needed)
//     cleanup();
//     exit(EXIT_SUCCESS);
// }