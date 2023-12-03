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

// Mouse event var
MEVENT event;
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

// Print message with drone real coordinates on top of COURT drawing
void draw_drone_msg(float x, float y, float vx, float vy) {

    for(int j = 0; j < COLS; j++) {
        mvaddch(court.starty - 2, j, ' ');
    }

    char msg[100];
    sprintf(msg, "Drone velocity [%05.2f vx,%.2f vy]                                      Drone position [%05.2f, %.2f]", vx, vy, x, y);

    attron(A_BOLD);
    mvprintw(court.starty - 2, (COLS - strlen(msg)) / 2 + 1, msg);
    attroff(A_BOLD);
}

// Draw drone within the structure
void draw_drone_at(float ee_x, float ee_y) {

    // First, empty all drawn content
     for(int j = 0; j < court.width; j++) {
        for(int i = 0; i < court.height; i++) {
            mvaddch(court.starty + i, court.startx + j, ' ');
        }
    }

    // // Convert  real coordinates to lower integer...
    // int ee_x_int = floor(ee_x);
    // int ee_y_int = floor(ee_y);

    attron(A_BOLD | COLOR_PAIR(1));
    mvaddch(court.starty + ee_y, court.startx + ee_x, '+');
    attroff(A_BOLD | COLOR_PAIR(1));
}

// Utility method to check for end-effector within limits
void check_drone_within_limits(float* ee_x, float* ee_y) {

    // Checks for horizontal axis
    if(*ee_x <= 0) {
        *ee_x = 0 ;
    }
    else if(*ee_x >= COURT_X_LIM) {
        *ee_x = COURT_X_LIM-1;
    }
   
    // Checks for vertical axis
    if(*ee_y <= 0) {
        *ee_y = 0 ;
    }
    else if(*ee_y >= COURT_Y_LIM) {
        *ee_y = COURT_Y_LIM-1;
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
    draw_drone_msg(0, 0, 0, 0);

    // Activate input listening (keybord + mouse events ...)
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    refresh();
}

void update_console_ui(float *ee_x, float *ee_y, float *vx, float *vy, BLACKBOARD_DATA *blackboard) {

    // check if next drone position is within limits
    check_drone_within_limits(ee_x, ee_y);

    // Draw updated drone position
    draw_drone_at(*ee_x,*ee_y);

    // Update string message for drone position
    draw_drone_msg(*ee_x, *ee_y, *vx, *vy);
    
    // Display blackboard data in the ncurses window
    mvprintw(2, 0, "Message on the Blackboard: %s", blackboard->message);

    refresh();

}

void reset_console_ui() {

    // Clear screen
    erase();

    // Re-create UI elements
    make_court();

    // draw UI elements
    draw_court();
    draw_drone_msg(0, 0, 0 ,0);

    refresh();
}