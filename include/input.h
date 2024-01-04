// #ifndef INPUT_H
#define INPUT_H

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

// Include other necessary modules
#include "drone.h"

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

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);

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