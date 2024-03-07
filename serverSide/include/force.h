#include "court.h"

#include <sys/stat.h> 
#include <sys/types.h> 

float fx = 0.0;
float fy = 0.0;

float fTx = 0.0;
float fTy = 0.0;

float D = 0.996;       // Drag ratio

float vx = 0.0;
float vy = 0.0;

float ee_x = 50.0;
float ee_y = 20.0;

int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10; 
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10; 
int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10; 
int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10; 

bool reachedGoal1 = 0, reachedGoal2 = 0, reachedGoal3 = 0, reachedGoal4 = 0, reachedGoal5 = 0, reachedGoal6 = 0, reachedGoal7 = 0, reachedGoal8 = 0, reachedGoal9 = 0, reachedGoal10 = 0;

bool reachedAllTheGoals = 1;
bool computation_in_progress = 0;

// void check_drone_within_limits() {

//     // Checks for horizontal axis
//     if(ee_x <= 0) {
//         ee_x = 0 ;
//     }
//     else if(ee_x >= COURT_X_LIM) {
//         ee_x = COURT_X_LIM-1;
//     }
   
//     // Checks for vertical axis
//     if(ee_y <= 0) {
//         ee_y = 0 ;
//     }
//     else if(ee_y >= COURT_Y_LIM) {
//         ee_y = COURT_Y_LIM-1;
//     }
// }