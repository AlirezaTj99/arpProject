#include "court.h"

#include <stdlib.h>
#include <time.h>

#include <sys/stat.h> 
#include <sys/types.h>

int ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10;
int oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10;

int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10;
int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10;

int max_x = 99; // The maximum value for x
int max_y = 39; // The maximum value for y

void spawn_random_g() {
    float ee_x, ee_y;

    gx1 = ox1;
    gy1 = oy1;

    srand(time(0));
    
    while((gx1 == ox1 && gy1 == oy1) || (gx2 == ox2 && gy2 == oy2) || (gx3 == ox3 && gy3 == oy3) || (gx4 == ox4 && gy4 == oy4) || (gx5 == ox5 && gy5 == oy5) ||
          (gx6 == ox6 && gy6 == oy6) || (gx7 == ox7 && gy7 == oy7) || (gx8 == ox8 && gy8 == oy8) || (gx9 == ox9 && gy9 == oy9) || (gx10== ox10 && gy10== oy10))
    {
        int min = 1; // The minimum positive value for x and y
        

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
    

    // printf("%d    ________    %d \n",ox1,gx1);
    // printf("%d    ________    %d \n",ox2,gx2);
    // printf("%d    ________    %d \n",ox3,gx3);
    // printf("%d    ________    %d \n",ox4,gx4);
    // printf("%d    ________    %d \n",ox5,gx5);
    // printf("%d    ________    %d \n",ox6,gx6);
    // printf("%d    ________    %d \n",ox7,gx7);
    // printf("%d    ________    %d \n",ox8,gx8);
    // printf("%d    ________    %d \n",ox9,gx9);
    // printf("%d    ________    %d \n",ox10,gx10);
    // printf("%d    ________    %d \n",oy1,gy1);
    // printf("%d    ________    %d \n",oy2,gy2);
    // printf("%d    ________    %d \n",oy3,gy3);
    // printf("%d    ________    %d \n",oy4,gy4);
    // printf("%d    ________    %d \n",oy5,gy5);
    // printf("%d    ________    %d \n",oy6,gy6);
    // printf("%d    ________    %d \n",oy7,gy7);
    // printf("%d    ________    %d \n",oy8,gy8);
    // printf("%d    ________    %d \n",oy9,gy9);
    // printf("%d    ________    %d \n",oy10,gy10);
}