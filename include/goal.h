#include "court.h"

#include <stdlib.h>
#include <time.h>

int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;

void importObstacleCoordinates(){

    ox1 = shared_data->ox1 ;
    ox2 = shared_data->ox2 ;
    ox3 = shared_data->ox3 ;
    ox4 = shared_data->ox4 ;
    ox5 = shared_data->ox5 ;
    ox6 = shared_data->ox6 ;
    ox7 = shared_data->ox7 ;
    ox8 = shared_data->ox8 ;
    ox9 = shared_data->ox9 ;
    ox10 = shared_data->ox10 ;

    oy1 = shared_data->oy1 ;
    oy2 = shared_data->oy2 ;
    oy3 = shared_data->oy3 ;
    oy4 = shared_data->oy4 ;
    oy5 = shared_data->oy5 ;
    oy6 = shared_data->oy6 ;
    oy7 = shared_data->oy7 ;
    oy8 = shared_data->oy8 ;
    oy9 = shared_data->oy9 ;
    oy10 = shared_data->oy10 ;
}

void spawn_random_g() {
    float ee_x, ee_y;
    int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10;
    int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10;

    // ee_x = shared_data->x;
    // ee_y = shared_data->y;
    gx1 = ox1;
    gy1 = oy1;

    srand(time(0));
    
    while((gx1 == ox1 && gy1 == oy1) || (gx2 == ox2 && gy2 == oy2) || (gx3 == ox3 && gy3 == oy3) || (gx4 == ox4 && gy4 == oy4) || (gx5 == ox5 && gy5 == oy5) ||
          (gx6 == ox6 && gy6 == oy6) || (gx7 == ox7 && gy7 == oy7) || (gx8 == ox8 && gy8 == oy8) || (gx9 == ox9 && gy9 == oy9) || (gx10== ox10 && gy10== oy10))
    {
        int min = 1; // The minimum positive value for x and y
        int max_x = COURT_X_LIM -2; // The maximum value for x
        int max_y = COURT_Y_LIM -2; // The maximum value for y

        gx1 = min + rand() % (max_x - min + 1);
        gx2 = min + rand() % (max_x - min + 1);
        gx3 = min + rand() % (max_x - min + 1);
        gx4 = min + rand() % (max_x - min + 1);
        gx5 = min + rand() % (max_x - min + 1);
        gx6 = min + rand() % (max_x - min + 1);
        gx7 = min + rand() % (max_x - min + 1);
        gx8 = min + rand() % (max_x - min + 1);
        gx9 = min + rand() % (max_x - min + 1);
        gx10 = min + rand() % (max_x - min + 1);

        gy1 = min + rand() % (max_y - min + 1);
        gy2 = min + rand() % (max_y - min + 1);
        gy3 = min + rand() % (max_y - min + 1);
        gy4 = min + rand() % (max_y - min + 1);
        gy5 = min + rand() % (max_y - min + 1);
        gy6 = min + rand() % (max_y - min + 1);
        gy7 = min + rand() % (max_y - min + 1);
        gy8 = min + rand() % (max_y - min + 1);
        gy9 = min + rand() % (max_y - min + 1);
        gy10 = min + rand() % (max_y - min + 1);

    }
    
    // Sending data to shared memory.
    shared_data->gx1 = gx1;
    shared_data->gx2 = gx2;
    shared_data->gx3 = gx3;
    shared_data->gx4 = gx4;
    shared_data->gx5 = gx5;
    shared_data->gx6 = gx6;
    shared_data->gx7 = gx7;
    shared_data->gx8 = gx8;
    shared_data->gx9 = gx9;
    shared_data->gx10 = gx10;

    shared_data->gy1 = gy1;
    shared_data->gy2 = gy2;
    shared_data->gy3 = gy3;
    shared_data->gy4 = gy4;
    shared_data->gy5 = gy5;
    shared_data->gy6 = gy6;
    shared_data->gy7 = gy7;
    shared_data->gy8 = gy8;
    shared_data->gy9 = gy9;
    shared_data->gy10 = gy10;

    printf("%.2f    ________    %d \n",ee_x,gx1);
    printf("%.2f    ________    %d \n",ee_x,gx2);
    printf("%.2f    ________    %d \n",ee_x,gx3);
    printf("%.2f    ________    %d \n",ee_x,gx4);
    printf("%.2f    ________    %d \n",ee_x,gx5);
    printf("%.2f    ________    %d \n",ee_x,gx6);
    printf("%.2f    ________    %d \n",ee_x,gx7);
    printf("%.2f    ________    %d \n",ee_x,gx8);
    printf("%.2f    ________    %d \n",ee_x,gx9);
    printf("%.2f    ________    %d \n",ee_x,gx10);
    printf("%.2f    ________    %d \n",ee_y,gy1);
    printf("%.2f    ________    %d \n",ee_y,gy2);
    printf("%.2f    ________    %d \n",ee_y,gy3);
    printf("%.2f    ________    %d \n",ee_y,gy4);
    printf("%.2f    ________    %d \n",ee_y,gy5);
    printf("%.2f    ________    %d \n",ee_y,gy6);
    printf("%.2f    ________    %d \n",ee_y,gy7);
    printf("%.2f    ________    %d \n",ee_y,gy8);
    printf("%.2f    ________    %d \n",ee_y,gy9);
    printf("%.2f    ________    %d \n",ee_y,gy10);
}