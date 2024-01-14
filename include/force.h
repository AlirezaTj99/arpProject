#include "court.h"

float fx = 0.0;
float fy = 0.0;

float vx = 0.0;
float vy = 0.0;

float ee_x = 0.0;
float ee_y = 0.0;

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