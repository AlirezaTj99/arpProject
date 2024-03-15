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

float ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, ox11, ox12, ox13, ox14, ox15, ox16, ox17, ox18, ox19, ox20; 
float oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10, oy11, oy12, oy13, oy14, oy15, oy16, oy17, oy18, oy19, oy20; 
float gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gx11, gx12, gx13, gx14, gx15, gx16, gx17, gx18, gx19, gx20; 
float gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10, gy11, gy12, gy13, gy14, gy15, gy16, gy17, gy18, gy19, gy20; 

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
char str9[1024];
char formatT2[1024]="T[2]%f,%f|%f,%f";
char formatT3[1024]="T[3]%f,%f|%f,%f|%f,%f";
char formatT4[1024]="T[4]%f,%f|%f,%f|%f,%f|%f,%f";
char formatT5[1024]="T[5]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT6[1024]="T[6]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT7[1024]="T[7]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT8[1024]="T[8]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT9[1024]="T[9]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT10[1024]="T[10]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT11[1024]="T[11]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT12[1024]="T[12]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT13[1024]="T[13]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT14[1024]="T[14]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT15[1024]="T[15]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT16[1024]="T[16]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT17[1024]="T[17]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT18[1024]="T[18]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT19[1024]="T[19]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatT20[1024]="T[20]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO2[1024]="O[2]%f,%f|%f,%f";
char formatO3[1024]="O[3]%f,%f|%f,%f|%f,%f";
char formatO4[1024]="O[4]%f,%f|%f,%f|%f,%f|%f,%f";
char formatO5[1024]="O[5]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO6[1024]="O[6]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO7[1024]="O[7]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO8[1024]="O[8]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO9[1024]="O[9]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO10[1024]="O[10]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO11[1024]="O[11]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO12[1024]="O[12]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO13[1024]="O[13]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO14[1024]="O[14]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO15[1024]="O[15]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO16[1024]="O[16]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO17[1024]="O[17]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO18[1024]="O[18]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO19[1024]="O[19]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";
char formatO20[1024]="O[20]%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f|%f,%f";


// void scan()
// {
//     if(str9[0]=='T')
//     {
//         printf(" It's a Target\n");
//         if (str9[2]=='2' && str9[3]==']'){sscanf(str9, formatT2, &gx1, &gy1, &gx2, &gy2);}
//         else if (str9[2]=='3' && str9[3]==']'){sscanf(str9, formatT3, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3);}
//         else if (str9[2]=='4' && str9[3]==']'){sscanf(str9, formatT4, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4);}
//         else if (str9[2]=='5' && str9[3]==']'){sscanf(str9, formatT5, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5);}
//         else if (str9[2]=='6' && str9[3]==']'){sscanf(str9, formatT6, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6);}
//         else if (str9[2]=='7' && str9[3]==']'){sscanf(str9, formatT7, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7);}
//         else if (str9[2]=='8' && str9[3]==']'){sscanf(str9, formatT8, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8);}
//         else if (str9[2]=='9' && str9[3]==']'){sscanf(str9, formatT9, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9);}
//         else if (str9[2]=='1' && str9[3]=='0'){sscanf(str9, formatT10, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10);}
//         else if (str9[2]=='1' && str9[3]=='1'){sscanf(str9, formatT11, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11);}
//         else if (str9[2]=='1' && str9[3]=='2'){sscanf(str9, formatT12, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12);}
//         else if (str9[2]=='1' && str9[3]=='3'){sscanf(str9, formatT13, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13);}
//         else if (str9[2]=='1' && str9[3]=='4'){sscanf(str9, formatT14, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14);}
//         else if (str9[2]=='1' && str9[3]=='5'){sscanf(str9, formatT15, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14, &gx15, &gy15);}
//         else if (str9[2]=='1' && str9[3]=='6'){sscanf(str9, formatT16, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14, &gx15, &gy15, &gx16, &gy16);}
//         else if (str9[2]=='1' && str9[3]=='7'){sscanf(str9, formatT17, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14, &gx15, &gy15, &gx16, &gy16, &gx17, &gy17);}
//         else if (str9[2]=='1' && str9[3]=='8'){sscanf(str9, formatT18, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14, &gx15, &gy15, &gx16, &gy16, &gx17, &gy17, &gx18, &gy18);}
//         else if (str9[2]=='1' && str9[3]=='9'){sscanf(str9, formatT19, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14, &gx15, &gy15, &gx16, &gy16, &gx17, &gy17, &gx18, &gy18, &gx19, &gy19);}
//         else if (str9[2]=='2' && str9[3]=='0'){sscanf(str9, formatT20, &gx1, &gy1, &gx2, &gy2, &gx3, &gy3, &gx4, &gy4, &gx5, &gy5, &gx6, &gy6, &gx7, &gy7, &gx8, &gy8, &gx9, &gy9, &gx10, &gy10, &gx11, &gy11, &gx12, &gy12, &gx13, &gy13, &gx14, &gy14, &gx15, &gy15, &gx16, &gy16, &gx17, &gy17, &gx18, &gy18, &gx19, &gy19, &gx20, &gy20);}
//         printf("the co_ordinates: %f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10, gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10);
//     }else if(str9[0]=='O')
//     {
//         printf(" It's an Obstacle\n");
//         if (str9[2]=='2' && str9[3]==']'){sscanf(str9, formatO2, &ox1, &oy1, &ox2, &oy2);}
//         else if (str9[2]=='3' && str9[3]==']'){sscanf(str9, formatO3, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3);}
//         else if (str9[2]=='4' && str9[3]==']'){sscanf(str9, formatO4, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4);}
//         else if (str9[2]=='5' && str9[3]==']'){sscanf(str9, formatO5, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5);}
//         else if (str9[2]=='6' && str9[3]==']'){sscanf(str9, formatO6, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6);}
//         else if (str9[2]=='7' && str9[3]==']'){sscanf(str9, formatO7, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7);}
//         else if (str9[2]=='8' && str9[3]==']'){sscanf(str9, formatO8, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8);}
//         else if (str9[2]=='9' && str9[3]==']'){sscanf(str9, formatO9, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9);}
//         else if (str9[2]=='1' && str9[3]=='0'){sscanf(str9, formatO10, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10);}
//         else if (str9[2]=='1' && str9[3]=='1'){sscanf(str9, formatO11, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11);}
//         else if (str9[2]=='1' && str9[3]=='2'){sscanf(str9, formatO12, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12);}
//         else if (str9[2]=='1' && str9[3]=='3'){sscanf(str9, formatO13, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13);}
//         else if (str9[2]=='1' && str9[3]=='4'){sscanf(str9, formatO14, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14);}
//         else if (str9[2]=='1' && str9[3]=='5'){sscanf(str9, formatO15, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14, &ox15, &oy15);}
//         else if (str9[2]=='1' && str9[3]=='6'){sscanf(str9, formatO16, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14, &ox15, &oy15, &ox16, &oy16);}
//         else if (str9[2]=='1' && str9[3]=='7'){sscanf(str9, formatO17, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14, &ox15, &oy15, &ox16, &oy16, &ox17, &oy17);}
//         else if (str9[2]=='1' && str9[3]=='8'){sscanf(str9, formatO18, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14, &ox15, &oy15, &ox16, &oy16, &ox17, &oy17, &ox18, &oy18);}
//         else if (str9[2]=='1' && str9[3]=='9'){sscanf(str9, formatO19, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14, &ox15, &oy15, &ox16, &oy16, &ox17, &oy17, &ox18, &oy18, &ox19, &oy19);}
//         else if (str9[2]=='2' && str9[3]=='0'){sscanf(str9, formatO20, &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10, &ox11, &oy11, &ox12, &oy12, &ox13, &oy13, &ox14, &oy14, &ox15, &oy15, &ox16, &oy16, &ox17, &oy17, &ox18, &oy18, &ox19, &oy19, &ox20, &oy20);}
//         printf("the co_ordinates: %f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", ox1, ox2, ox3, ox4, ox5, ox6, ox7, ox8, ox9, ox10, oy1, oy2, oy3, oy4, oy5, oy6, oy7, oy8, oy9, oy10);
//     }
// }