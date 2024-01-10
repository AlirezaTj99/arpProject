#include "court.h"

#include <stdlib.h>
#include <time.h>

void spawn_random_o() {
    float ee_x, ee_y;
    int x1, x2, x3, x4, x5, x6, x7, x8, x9, x10;
    int y1, y2, y3, y4, y5, y6, y7, y8, y9, y10;

    ee_x = shared_data->x;
    ee_y = shared_data->y;
    x1 = ee_x;
    y1 = ee_y;

    srand(time(0));
    
    while(((ee_x - 2) < x1 && (ee_x + 2) > x1) && ((ee_y - 2) < y1 && (ee_y + 2) > y1) ||
          ((ee_x - 2) < x2 && (ee_x + 2) > x2) && ((ee_y - 2) < y2 && (ee_y + 2) > y2) ||
          ((ee_x - 2) < x3 && (ee_x + 2) > x3) && ((ee_y - 2) < y3 && (ee_y + 2) > y3) ||
          ((ee_x - 2) < x4 && (ee_x + 2) > x4) && ((ee_y - 2) < y4 && (ee_y + 2) > y4) ||
          ((ee_x - 2) < x5 && (ee_x + 2) > x5) && ((ee_y - 2) < y5 && (ee_y + 2) > y5)  )
    {
        int min = 1; // The minimum positive value for x and y
        int max_x = COURT_X_LIM; // The maximum value for x
        int max_y = COURT_Y_LIM; // The maximum value for y

        x1 = min + rand() % (max_x - min + 1);
        x2 = min + rand() % (max_x - min + 1);
        x3 = min + rand() % (max_x - min + 1);
        x4 = min + rand() % (max_x - min + 1);
        x5 = min + rand() % (max_x - min + 1);
        x6 = min + rand() % (max_x - min + 1);
        x7 = min + rand() % (max_x - min + 1);
        x8 = min + rand() % (max_x - min + 1);
        x9 = min + rand() % (max_x - min + 1);
        x10 = min + rand() % (max_x - min + 1);

        y1 = min + rand() % (max_y - min + 1);
        y2 = min + rand() % (max_y - min + 1);
        y3 = min + rand() % (max_y - min + 1);
        y4 = min + rand() % (max_y - min + 1);
        y5 = min + rand() % (max_y - min + 1);
        y6 = min + rand() % (max_y - min + 1);
        y7 = min + rand() % (max_y - min + 1);
        y8 = min + rand() % (max_y - min + 1);
        y9 = min + rand() % (max_y - min + 1);
        y10 = min + rand() % (max_y - min + 1);

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

    printf("%.2f    ________    %d \n",ee_x,x1);
    printf("%.2f    ________    %d \n",ee_x,x2);
    printf("%.2f    ________    %d \n",ee_x,x3);
    printf("%.2f    ________    %d \n",ee_x,x4);
    printf("%.2f    ________    %d \n",ee_x,x5);
    printf("%.2f    ________    %d \n",ee_x,x6);
    printf("%.2f    ________    %d \n",ee_x,x7);
    printf("%.2f    ________    %d \n",ee_x,x8);
    printf("%.2f    ________    %d \n",ee_x,x9);
    printf("%.2f    ________    %d \n",ee_x,x10);
    printf("%.2f    ________    %d \n",ee_y,y1);
    printf("%.2f    ________    %d \n",ee_y,y2);
    printf("%.2f    ________    %d \n",ee_y,y3);
    printf("%.2f    ________    %d \n",ee_y,y4);
    printf("%.2f    ________    %d \n",ee_y,y5);
    printf("%.2f    ________    %d \n",ee_y,y6);
    printf("%.2f    ________    %d \n",ee_y,y7);
    printf("%.2f    ________    %d \n",ee_y,y8);
    printf("%.2f    ________    %d \n",ee_y,y9);
    printf("%.2f    ________    %d \n",ee_y,y10);
}