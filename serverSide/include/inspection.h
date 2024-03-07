#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <ncurses.h>

#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

#include <sys/stat.h> 
#include <errno.h>

int pid_input, pid_force, pid_client, pid_watchdog;

bool inputIsRunning = 0, forceIsRunning = 0, clientIsRunning = 0, watchdogIsRunning = 0;


// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483