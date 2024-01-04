// #ifndef COURT_H
#define COURT_H

// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <ncurses.h>

#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

typedef struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}COURT_BORDER;

typedef struct {
	int startx, starty;
	int height, width;
	COURT_BORDER border;
} COURT;

typedef struct {
    char message[100];
} BLACKBOARD_DATA;

typedef struct {
    volatile sig_atomic_t close_master;  // Flag to signal master to close
    volatile sig_atomic_t computation_in_progress; // Flag to indicate computation in progress
    float ee_x;
    float ee_y;
    float vx;
    float vy;
} SHARED_DATA;

int MAX_MESSAGE_LENGTH = 100;
int COURT_X_LIM = 101;
int COURT_Y_LIM = 41;

// COURT structure variable
COURT court;

BLACKBOARD_DATA *blackboard;
SHARED_DATA *shared_data;

// Initialize court structure and parameters
void make_court() {

    court.height = COURT_Y_LIM;
    court.width = COURT_X_LIM;
    court.starty = (LINES - court.height)/2 + 4;	
    court.startx = (COLS - court.width)/2;

    court.border.ls = ACS_VLINE;
    court.border.rs = ACS_VLINE;
    court.border.ts = ACS_HLINE;
    court.border.bs = ACS_HLINE;
    court.border.tl = ACS_ULCORNER;
    court.border.tr = ACS_URCORNER;
    court.border.bl = ACS_LLCORNER;
    court.border.br = ACS_LRCORNER;
}

void draw_court() {  
    
    int x, y, w, h;

    x = court.startx;
    y = court.starty;
    w = court.width;
    h = court.height;

    // Draw top corners and horizontal structure
    mvaddch(y - 1, x - 2, court.border.tl);
    mvaddch(y - 1, x + w + 1, court.border.tr);
    mvhline(y - 1, x - 1, court.border.ts, w + 2);

    // Draw bottom corners and side structures
    mvaddch(y + h , x - 2, court.border.bl);
    mvaddch(y + h , x + w + 1, court.border.br);
    mvvline(y, x - 2, court.border.ls, h);
    mvvline(y, x + w + 1 , court.border.rs, h);

    // Draw reference floor
    mvhline(y + h , x - 1, court.border.bs, w + 2);

    refresh();
}