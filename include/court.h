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
    volatile sig_atomic_t close_master;            // Flag to signal master to close
    volatile sig_atomic_t computation_in_progress; // Flag to indicate computation in progress
    volatile sig_atomic_t reachedAllTheGoals;      // Flag to indicate the player reached all the goals
    volatile sig_atomic_t xForceIncrease;          // Flag to indicate Fx++
    volatile sig_atomic_t xForceDecrease;          // Flag to indicate Fx--
    volatile sig_atomic_t yForceIncrease;          // Flag to indicate Fy++
    volatile sig_atomic_t yForceDecrease;          // Flag to indicate Fy--
    volatile sig_atomic_t zeroForce;               // Flag to indicate Fy = Fx = 0
    volatile sig_atomic_t ox1;
    volatile sig_atomic_t ox2;
    volatile sig_atomic_t ox3;
    volatile sig_atomic_t ox4;
    volatile sig_atomic_t ox5;
    volatile sig_atomic_t ox6;
    volatile sig_atomic_t ox7;
    volatile sig_atomic_t ox8;
    volatile sig_atomic_t ox9;
    volatile sig_atomic_t ox10;
    volatile sig_atomic_t oy1;
    volatile sig_atomic_t oy2;
    volatile sig_atomic_t oy3;
    volatile sig_atomic_t oy4;
    volatile sig_atomic_t oy5;
    volatile sig_atomic_t oy6;
    volatile sig_atomic_t oy7;
    volatile sig_atomic_t oy8;
    volatile sig_atomic_t oy9;
    volatile sig_atomic_t oy10;
    volatile sig_atomic_t x;
    volatile sig_atomic_t y;
    volatile sig_atomic_t Vx;
    volatile sig_atomic_t Vy;
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