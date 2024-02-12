#include "court.h"

#include <stdlib.h>
#include <time.h>

#include <sys/stat.h> 
#include <sys/types.h> 

float ee_x, ee_y;

int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;

void spawn_random_o() {
    
    ox1 = ee_x;
    oy1 = ee_y;

    srand(time(0));
    
    while(((ee_x - 6) < ox1 && (ee_x + 6) > ox1) && ((ee_y - 6) < oy1 && (ee_y + 6) > oy1) ||
          ((ee_x - 6) < ox2 && (ee_x + 6) > ox2) && ((ee_y - 6) < oy2 && (ee_y + 6) > oy2) ||
          ((ee_x - 6) < ox3 && (ee_x + 6) > ox3) && ((ee_y - 6) < oy3 && (ee_y + 6) > oy3) ||
          ((ee_x - 6) < ox4 && (ee_x + 6) > ox4) && ((ee_y - 6) < oy4 && (ee_y + 6) > oy4) ||
          ((ee_x - 6) < ox5 && (ee_x + 6) > ox5) && ((ee_y - 6) < oy5 && (ee_y + 6) > oy5) ||
          ((ee_x - 6) < ox6 && (ee_x + 6) > ox6) && ((ee_y - 6) < oy6 && (ee_y + 6) > oy6) ||
          ((ee_x - 6) < ox7 && (ee_x + 6) > ox7) && ((ee_y - 6) < oy7 && (ee_y + 6) > oy7) ||
          ((ee_x - 6) < ox8 && (ee_x + 6) > ox8) && ((ee_y - 6) < oy8 && (ee_y + 6) > oy8) ||
          ((ee_x - 6) < ox9 && (ee_x + 6) > ox9) && ((ee_y - 6) < oy9 && (ee_y + 6) > oy9) ||
          ((ee_x - 6) < ox10 && (ee_x + 6) > ox10) && ((ee_y - 6) < oy10 && (ee_y + 6) > oy10))
    {
        int min = 2; // The minimum positive value for x and y
        int max_x = COURT_X_LIM-2; // The maximum value for x
        int max_y = COURT_Y_LIM-2; // The maximum value for y

        ox1 = min + rand() % (max_x - min + 1);
        ox2 = min + rand() % (max_x - min + 1);
        ox3 = min + rand() % (max_x - min + 1);
        ox4 = min + rand() % (max_x - min + 1);
        ox5 = min + rand() % (max_x - min + 1);
        ox6 = min + rand() % (max_x - min + 1);
        ox7 = min + rand() % (max_x - min + 1);
        ox8 = min + rand() % (max_x - min + 1);
        ox9 = min + rand() % (max_x - min + 1);
        ox10 = min + rand() % (max_x - min + 1);

        oy1 = min + rand() % (max_y - min + 1);
        oy2 = min + rand() % (max_y - min + 1);
        oy3 = min + rand() % (max_y - min + 1);
        oy4 = min + rand() % (max_y - min + 1);
        oy5 = min + rand() % (max_y - min + 1);
        oy6 = min + rand() % (max_y - min + 1);
        oy7 = min + rand() % (max_y - min + 1);
        oy8 = min + rand() % (max_y - min + 1);
        oy9 = min + rand() % (max_y - min + 1);
        oy10 = min + rand() % (max_y - min + 1);
    }
    // // Sending data to shared memory.
    // shared_data->ox1 = x1;
    // shared_data->ox2 = x2;
    // shared_data->ox3 = x3;
    // shared_data->ox4 = x4;
    // shared_data->ox5 = x5;
    // shared_data->ox6 = x6;
    // shared_data->ox7 = x7;
    // shared_data->ox8 = x8;
    // shared_data->ox9 = x9;
    // shared_data->ox10 = x10;
    // shared_data->oy1 = y1;
    // shared_data->oy2 = y2;
    // shared_data->oy3 = y3;
    // shared_data->oy4 = y4;
    // shared_data->oy5 = y5;
    // shared_data->oy6 = y6;
    // shared_data->oy7 = y7;
    // shared_data->oy8 = y8;
    // shared_data->oy9 = y9;
    // shared_data->oy10 = y10;

    printf("%.2f    ________    %d \n",ee_x,ox1);
    printf("%.2f    ________    %d \n",ee_x,ox2);
    printf("%.2f    ________    %d \n",ee_x,ox3);
    printf("%.2f    ________    %d \n",ee_x,ox4);
    printf("%.2f    ________    %d \n",ee_x,ox5);
    printf("%.2f    ________    %d \n",ee_x,ox6);
    printf("%.2f    ________    %d \n",ee_x,ox7);
    printf("%.2f    ________    %d \n",ee_x,ox8);
    printf("%.2f    ________    %d \n",ee_x,ox9);
    printf("%.2f    ________    %d \n",ee_x,ox10);
    printf("%.2f    ________    %d \n",ee_y,oy1);
    printf("%.2f    ________    %d \n",ee_y,oy2);
    printf("%.2f    ________    %d \n",ee_y,oy3);
    printf("%.2f    ________    %d \n",ee_y,oy4);
    printf("%.2f    ________    %d \n",ee_y,oy5);
    printf("%.2f    ________    %d \n",ee_y,oy6);
    printf("%.2f    ________    %d \n",ee_y,oy7);
    printf("%.2f    ________    %d \n",ee_y,oy8);
    printf("%.2f    ________    %d \n",ee_y,oy9);
    printf("%.2f    ________    %d \n",ee_y,oy10);
}