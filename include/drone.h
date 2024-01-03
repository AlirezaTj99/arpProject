// #ifndef DRONE_H
#define DRONE_H

// Include other necessary modules
#include "court.h"

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

// // Define any structures, enums, or constants specific to the drone
// typedef struct {
//     float dx;   // X coordinate of the drone
//     float dy;   // Y coordinate of the drone
//     float vx;   // drone's velocity in X direction
//     float vy;   // drone's velocity in Y direction
// } Drone;

// // Function declarations

// /**
//  * Draws or prints messages related to the drone's coordinates and velocity.
//  * 
//  * @param dx  X coordinate of the drone.
//  * @param dy  Y coordinate of the drone.
//  * @param vx  X component of the drone's velocity.
//  * @param vy  Y component of the drone's velocity.
//  */
// void draw_drone_msg(float dx, float dy, float vx, float vy);

// /**
//  * Draws the drone at a specified position.
//  * 
//  * @param ee_x  X coordinate of the drone (drone's position).
//  * @param ee_y  Y coordinate of the drone (drone's position).
//  */
// void draw_drone_at(float ee_x, float ee_y);

// /**
//  * Checks if the drone's next position is within certain limits.
//  * 
//  * @param ee_x  Pointer to X coordinate of the end-effector (drone's position).
//  * @param ee_y  Pointer to Y coordinate of the end-effector (drone's position).
//  */
// void check_drone_within_limits(float* ee_x, float* ee_y);

// #endif // DRONE_H