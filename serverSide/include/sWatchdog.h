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

int pid_obstacle, pid_goal, pid_server;
int i =1;

bool goalIsRunning = 0, obstacleIsRunning = 0, serverIsRunning = 0;

bool masterTerminate = 1;


// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483