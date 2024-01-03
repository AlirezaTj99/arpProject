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

typedef struct {
    volatile sig_atomic_t computation_in_progress;
} SHARED_DATA;

SHARED_DATA *shared_data;

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        shared_data->computation_in_progress = 1;
    }
}