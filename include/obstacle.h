#include "court.h"

#include <stdlib.h>
#include <time.h>

void spawn_random_o() {
    float ee_x, ee_y;
    float x1, x2, x3, x4, x5, x6, x7, x8, x9, x10;
    float y1, y2, y3, y4, y5, y6, y7, y8, y9, y10;

    ee_x = shared_data->x;
    ee_y = shared_data->y;
    x1 = ee_x;
    y1 = ee_y;
    sleep(1);
    
    while(((ee_x - 2) < x1 && (ee_x + 2) > x1) && ((ee_y - 2) < y1 && (ee_y + 2) > y1) ||
          ((ee_x - 2) < x2 && (ee_x + 2) > x2) && ((ee_y - 2) < y2 && (ee_y + 2) > y2) ||
          ((ee_x - 2) < x3 && (ee_x + 2) > x3) && ((ee_y - 2) < y3 && (ee_y + 2) > y3) ||
          ((ee_x - 2) < x4 && (ee_x + 2) > x4) && ((ee_y - 2) < y4 && (ee_y + 2) > y4) ||
          ((ee_x - 2) < x5 && (ee_x + 2) > x5) && ((ee_y - 2) < y5 && (ee_y + 2) > y5)  )
    {
        x1 = rand() % COURT_X_LIM;
        x2 = rand() % COURT_X_LIM;
        x3 = rand() % COURT_X_LIM;
        x4 = rand() % COURT_X_LIM;
        x5 = rand() % COURT_X_LIM;
        x6 = rand() % COURT_X_LIM;
        x7 = rand() % COURT_X_LIM;
        x8 = rand() % COURT_X_LIM;
        x9 = rand() % COURT_X_LIM;
        x10 = rand() % COURT_X_LIM;
        y1 = rand() % COURT_Y_LIM;
        y2 = rand() % COURT_Y_LIM;
        y3 = rand() % COURT_Y_LIM;
        y4 = rand() % COURT_Y_LIM;
        y5 = rand() % COURT_Y_LIM;
        y6 = rand() % COURT_Y_LIM;
        y7 = rand() % COURT_Y_LIM;
        y8 = rand() % COURT_Y_LIM;
        y9 = rand() % COURT_Y_LIM;
        y10 = rand() % COURT_Y_LIM;
    }
    // Sending data to shared memory.
    shared_data->ox1 = x1;
    shared_data->ox2 = x2;
    shared_data->ox3 = x3;
    shared_data->ox4 = x4;
    shared_data->ox5 = x5;
    shared_data->ox6 = x6;
    shared_data->ox7 = x7;
    shared_data->ox8 = x8;
    shared_data->ox9 = x9;
    shared_data->ox10 = x10;
    shared_data->oy1 = y1;
    shared_data->oy2 = y2;
    shared_data->oy3 = y3;
    shared_data->oy4 = y4;
    shared_data->oy5 = y5;
    shared_data->oy6 = y6;
    shared_data->oy7 = y7;
    shared_data->oy8 = y8;
    shared_data->oy9 = y9;
    shared_data->oy10 = y10;

    printf("%.2f    ________    %.2f \n",ee_x,x1);
    printf("%.2f    ________    %.2f \n",ee_x,x2);
    printf("%.2f    ________    %.2f \n",ee_x,x3);
    printf("%.2f    ________    %.2f \n",ee_x,x4);
    printf("%.2f    ________    %.2f \n",ee_x,x5);
    printf("%.2f    ________    %.2f \n",ee_y,y1);
    printf("%.2f    ________    %.2f \n",ee_y,y2);
    printf("%.2f    ________    %.2f \n",ee_y,y3);
    printf("%.2f    ________    %.2f \n",ee_y,y4);
    printf("%.2f    ________    %.2f \n",ee_y,y5);
}