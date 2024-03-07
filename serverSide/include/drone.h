// #ifndef DRONE_H
#define DRONE_H

// Include other necessary modules
#include "court.h"

float ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
float oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;

float gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10;
float gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10;



bool reachedGoal1 = 0, reachedGoal2 = 0, reachedGoal3 = 0, reachedGoal4 = 0, reachedGoal5 = 0, reachedGoal6 = 0, reachedGoal7 = 0, reachedGoal8 = 0, reachedGoal9 = 0, reachedGoal10 = 0;

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

    // int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
    // int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;

    // ox1 = shared_data->ox1 ;
    // ox2 = shared_data->ox2 ;
    // ox3 = shared_data->ox3 ;
    // ox4 = shared_data->ox4 ;
    // ox5 = shared_data->ox5 ;
    // ox6 = shared_data->ox6 ;
    // ox7 = shared_data->ox7 ;
    // ox8 = shared_data->ox8 ;
    // ox9 = shared_data->ox9 ;
    // ox10 = shared_data->ox10 ;

    // oy1 = shared_data->oy1 ;
    // oy2 = shared_data->oy2 ;
    // oy3 = shared_data->oy3 ;
    // oy4 = shared_data->oy4 ;
    // oy5 = shared_data->oy5 ;
    // oy6 = shared_data->oy6 ;
    // oy7 = shared_data->oy7 ;
    // oy8 = shared_data->oy8 ;
    // oy9 = shared_data->oy9 ;
    // oy10 = shared_data->oy10 ;

    attron(A_BOLD | COLOR_PAIR(2));
    mvaddch(court.starty + oy1, court.startx + ox1, 'O');
    mvaddch(court.starty + oy2, court.startx + ox2, 'O');
    mvaddch(court.starty + oy3, court.startx + ox3, 'O');
    mvaddch(court.starty + oy4, court.startx + ox4, 'O');
    mvaddch(court.starty + oy5, court.startx + ox5, 'O');
    mvaddch(court.starty + oy6, court.startx + ox6, 'O');
    mvaddch(court.starty + oy7, court.startx + ox7, 'O');
    mvaddch(court.starty + oy8, court.startx + ox8, 'O');
    mvaddch(court.starty + oy9, court.startx + ox9, 'O');
    mvaddch(court.starty + oy10, court.startx + ox10, 'O');
    attroff(A_BOLD | COLOR_PAIR(2));

    // gx1 = shared_data->gx1 ;
    // gx2 = shared_data->gx2 ;
    // gx3 = shared_data->gx3 ;
    // gx4 = shared_data->gx4 ;
    // gx5 = shared_data->gx5 ;
    // gx6 = shared_data->gx6 ;
    // gx7 = shared_data->gx7 ;
    // gx8 = shared_data->gx8 ;
    // gx9 = shared_data->gx9 ;
    // gx10 = shared_data->gx10 ;

    // gy1 = shared_data->gy1 ;
    // gy2 = shared_data->gy2 ;
    // gy3 = shared_data->gy3 ;
    // gy4 = shared_data->gy4 ;
    // gy5 = shared_data->gy5 ;
    // gy6 = shared_data->gy6 ;
    // gy7 = shared_data->gy7 ;
    // gy8 = shared_data->gy8 ;
    // gy9 = shared_data->gy9 ;
    // gy10 = shared_data->gy10 ;

    attron(A_BOLD | COLOR_PAIR(3));
    if(!reachedGoal1)
        {
        mvaddch(court.starty + gy1, court.startx + gx1, '1');
        }
    if(!reachedGoal2)
        {
        mvaddch(court.starty + gy2, court.startx + gx2, '2');
        }
    if(!reachedGoal3)
        {
        mvaddch(court.starty + gy3, court.startx + gx3, '3');
        }
    if(!reachedGoal4)
        {
        mvaddch(court.starty + gy4, court.startx + gx4, '4');
        }
    if(!reachedGoal5)
        {
        mvaddch(court.starty + gy5, court.startx + gx5, '5');
        }
    if(!reachedGoal6)
        {
        mvaddch(court.starty + gy6, court.startx + gx6, '6');
        }
    if(!reachedGoal7)
        {
        mvaddch(court.starty + gy7, court.startx + gx7, '7');
        }
    if(!reachedGoal8)
        {
        mvaddch(court.starty + gy8, court.startx + gx8, '8');
        }
    if(!reachedGoal9)
        {
        mvaddch(court.starty + gy9, court.startx + gx9, '9');
        }
    if(!reachedGoal10)
        {
        mvaddch(court.starty + gy10, court.startx + gx10, '0');
        }
    attroff(A_BOLD | COLOR_PAIR(3));

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