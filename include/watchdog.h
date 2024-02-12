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

#include <sys/stat.h> 
#include <sys/types.h> 

#include "./court.h"


int no_computation_count = 1;

bool computation_in_progress = 0;

