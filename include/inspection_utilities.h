#include <ncurses.h>
#include <string.h>
#include <unistd.h> 
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}HOIST_BORDER;

typedef struct {
	int startx, starty;
	int height, width;
	HOIST_BORDER border;
}HOIST;

typedef struct {
    char message[100];
} BLACKBOARD_DATA;

typedef struct {
    float ee_x;
    float ee_y;
    int vx;
    int vy;
} SHARED_DATA;

int MAX_MESSAGE_LENGTH = 100;
int HOIST_X_LIM = 101;
int HOIST_Y_LIM = 41;

// Hoist structure variable
HOIST hoist;

// Mouse event var
MEVENT event;
BLACKBOARD_DATA *blackboard;

// Initialize hoist structure and parameters
void make_hoist() {

	hoist.height = HOIST_Y_LIM;
	hoist.width = HOIST_X_LIM;
	hoist.starty = (LINES - hoist.height)/2 + 4;	
	hoist.startx = (COLS - hoist.width)/2;

  hoist.border.ls = ACS_VLINE;
  hoist.border.rs = ACS_VLINE;
  hoist.border.ts = ACS_HLINE;
  hoist.border.bs = ACS_HLINE;
  hoist.border.tl = ACS_ULCORNER;
  hoist.border.tr = ACS_URCORNER;
  hoist.border.bl = ACS_LLCORNER;
  hoist.border.br = ACS_LRCORNER;
}

void draw_hoist() {  
  
    int x, y, w, h;

  x = hoist.startx;
  y = hoist.starty;
  w = hoist.width;
  h = hoist.height;

    // Draw top corners and horizontal structure
    mvaddch(y - 1, x - 2, hoist.border.tl);
    mvaddch(y - 1, x + w + 1, hoist.border.tr);
    mvhline(y - 1, x - 1, hoist.border.ts, w + 2);

    // Draw bottom corners and side structures
    mvaddch(y + h , x - 2, hoist.border.bl);
    mvaddch(y + h , x + w + 1, hoist.border.br);
    mvvline(y, x - 2, hoist.border.ls, h);
    mvvline(y, x + w + 1 , hoist.border.rs, h);

    // Draw reference floor
    mvhline(y + h , x - 1, hoist.border.bs, w + 2);

    refresh();
}

// Print message with end-effector real coordinates on top of hoist drawing
void draw_end_effector_msg(float x, float y, float vx, float vy) {

    for(int j = 0; j < COLS; j++) {
        mvaddch(hoist.starty - 2, j, ' ');
    }

    char msg[100];
    sprintf(msg, "Drone velocity [%05.2f vx,%.2f vy]                                      Drone position [%05.2f, %.2f]", vx, vy, x, y);

    attron(A_BOLD);
    mvprintw(hoist.starty - 2, (COLS - strlen(msg)) / 2 + 1, msg);
    attroff(A_BOLD);
}

// Draw hoist's end-effector within the structure
void draw_hoist_end_effector_at(float ee_x, float ee_y) {

    // First, empty all drawn content
     for(int j = 0; j < hoist.width; j++) {
        for(int i = 0; i < hoist.height; i++) {
            mvaddch(hoist.starty + i, hoist.startx + j, ' ');
        }
    }

    // // Convert  real coordinates to lower integer...
    // int ee_x_int = floor(ee_x);
    // int ee_y_int = floor(ee_y);

    attron(A_BOLD | COLOR_PAIR(1));
    mvaddch(hoist.starty + ee_y, hoist.startx + ee_x, '+');
    attroff(A_BOLD | COLOR_PAIR(1));
}

// Utility method to check for end-effector within limits
void check_ee_within_limits(float* ee_x, float* ee_y) {

    // Checks for horizontal axis
    if(*ee_x <= 0) {
        *ee_x = 0 ;
    }
    else if(*ee_x >= HOIST_X_LIM) {
        *ee_x = HOIST_X_LIM-1;
    }
   
    // Checks for vertical axis
    if(*ee_y <= 0) {
        *ee_y = 0 ;
    }
    else if(*ee_y >= HOIST_Y_LIM) {
        *ee_y = HOIST_Y_LIM-1;
    }
}

void init_console_ui() {

    // Initialize curses mode
    initscr();		
	start_color();

    // Disable line buffering...
	cbreak();

    // Disable char echoing and blinking cursos
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_BLACK,   COLOR_YELLOW);

    // draw UI elements
    draw_end_effector_msg(0, 0, 0, 0);

    // Activate input listening (keybord + mouse events ...)
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    refresh();
}

void update_console_ui(float *ee_x, float *ee_y, int *vx, int *vy, BLACKBOARD_DATA *blackboard) {

    // check if next end-effector position is within limits
    check_ee_within_limits(ee_x, ee_y);

    // Draw updated end-effector position
    draw_hoist_end_effector_at(*ee_x,*ee_y);

    // Update string message for end-effector position
    draw_end_effector_msg(*ee_x, *ee_y, *vx, *vy);
    
    // Display blackboard data in the ncurses window
    mvprintw(2, 0, "Message on the Blackboard: %s", blackboard->message);

    refresh();

}

void reset_console_ui() {

    // Clear screen
    erase();

    // Re-create UI elements
    make_hoist();

    // draw UI elements
    draw_hoist();
    draw_end_effector_msg(0, 0, 0 ,0);

    refresh();
}