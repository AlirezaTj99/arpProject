#include "./../include/force.h"

int main(){

    int fd2; 
    char * myfifo2 = "/tmp/myfifo2"; 
    mkfifo(myfifo2, 0666); 
    char str2[80]; 
    char format_string[80]="%d";
    int keySignal = 0;

    int fd3;
    char * myfifo3 = "/tmp/myfifo3";
    mkfifo(myfifo3, 0666);
    char str3[80];
    char format_string3[80]="%d,%f,%f,%f,%f";

    // int fd6;
    // char * myfifo6 = "/tmp/myfifo6";
    // mkfifo(myfifo6, 0666);
    // char str6[256];
    // char format_string6[70] = "%d,%d|%d,%d|%d,%d|%d,%d|%d,%d|%d,%d|%d,%d|%d,%d|%d,%d|%d,%d";

    // int fd4;
    // char * myfifo4 = "/tmp/myfifo4";
    // mkfifo(myfifo4, 0666);
    // char str4[80];
    // char format_string4[80]="%f,%f";

    int fd8;
    char * myfifo8 = "/tmp/myfifo8";
    mkfifo(myfifo8, 0666);
    char str8[160];
    char format_string8[160]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    int fd10;
    char * myfifo10 = "/tmp/myfifo10";
    mkfifo(myfifo10, 0666);
    char str10[80];
    char format_string10[80]="%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

    // int fd11; 
    // char * myfifo11 = "/tmp/myfifo11"; 
    // mkfifo(myfifo11, 0666); 
    // char str11[80]; 
    // char format_string11[80]="%d";

    // int fd12; 
    // char * myfifo12 = "/tmp/myfifo12"; 
    // mkfifo(myfifo12, 0666); 
    // char str12[80]; 
    // char format_string12[80]="%d";

    int fd13; 
    char * myfifo13 = "/tmp/myfifo13"; 
    mkfifo(myfifo13, 0666); 
    char str13[80]; 
    char format_string13[80]="%d";

    while(TRUE)
    {
        float Fx=0.0, Fox1=0.0, Fox2=0.0, Fox3=0.0, Fox4=0.0, Fox5=0.0, Fox6=0.0, Fox7=0.0, Fox8=0.0, Fox9=0.0, Fox10=0.0;
        float Fy=0.0, Foy1=0.0, Foy2=0.0, Foy3=0.0, Foy4=0.0, Foy5=0.0, Foy6=0.0, Foy7=0.0, Foy8=0.0, Foy9=0.0, Foy10=0.0;

        float Fgx1=0.0, Fgx2=0.0, Fgx3=0.0, Fgx4=0.0, Fgx5=0.0, Fgx6=0.0, Fgx7=0.0, Fgx8=0.0, Fgx9=0.0, Fgx10=0.0;
        float Fgy1=0.0, Fgy2=0.0, Fgy3=0.0, Fgy4=0.0, Fgy5=0.0, Fgy6=0.0, Fgy7=0.0, Fgy8=0.0, Fgy9=0.0, Fgy10=0.0;
        fd2 = open(myfifo2,O_RDONLY);
        if (fd2 == -1) {
            perror("Error opening FIFO2");
        }
        read(fd2, str2, 80); 
        sscanf(str2, format_string, &keySignal);
        if(keySignal == 1)
        {
            fx--;
            fy++;
        }
        else if(keySignal == 2)
        {
            fy++;
        }
        else if(keySignal == 3)
        {
            fx++;
            fy++;
        }
        else if(keySignal == 4)
        {
            fx--;
        }
        else if(keySignal == 5)
        {
            fx = 0;
            fy = 0;
        }
        else if(keySignal == 6)
        {
            fx++;
        }
        else if(keySignal == 7)
        {
            fx--;
            fy--;
        }
        else if(keySignal == 8)
        {
            fy--;
        }
        else if(keySignal == 9)
        {
            fx++;
            fy--;
        }
        printf("..........%d\n",keySignal);
        close(fd2);

        // if (reachedGoal1 && reachedGoal2 && reachedGoal3 && reachedGoal4 && reachedGoal5 &&
        //     reachedGoal6 && reachedGoal7 && reachedGoal8 && reachedGoal9 && reachedGoal10 )
        // {
        //     sleep(2);
        //     reachedAllTheGoals = 1;
        //     reachedGoal1 = 0, reachedGoal2 = 0, reachedGoal3 = 0, reachedGoal4 = 0, reachedGoal5 = 0, reachedGoal6 = 0, reachedGoal7 = 0, reachedGoal8 = 0, reachedGoal9 = 0, reachedGoal10 = 0;
        // }

        fd3 = open(myfifo3,O_WRONLY);               // Send the drone data to input processor
        if (fd3 == -1) {
            perror("Error opening FIFO3");
        }
        sprintf(str3, format_string3, reachedAllTheGoals, ee_x, ee_y, vx, vy);
        write(fd3, str3, strlen(str3)+1);
        close(fd3);

    //     fd6 = open(myfifo6,O_RDONLY);
    //     if (fd6 == -1) {
    //         perror("Error opening FIFO6");
    //     }
    //     read(fd6, str6, 256); 
    // //     sscanf(str6, format_string6, 
    // //    &ox1, &oy1, &ox2, &oy2, &ox3, &oy3, &ox4, &oy4, &ox5, &oy5, 
    // //    &ox6, &oy6, &ox7, &oy7, &ox8, &oy8, &ox9, &oy9, &ox10, &oy10);
    //     close(fd6);
        
    //     printf("str6: %s  \n", str6);

        // if(reachedAllTheGoals)
        // {
        //     fd8 = open(myfifo8,O_RDONLY);               // Import the obstacles position
        //     if (fd8 == -1) {
        //         perror("Error opening FIFO8");
        //     }
        //     read(fd8, str8, 160);
        //     sscanf(str8, format_string8, &ox1, &ox2, &ox3, &ox4, &ox5, &ox6, &ox7, &ox8, &ox9, &ox10, &oy1, &oy2, &oy3, &oy4, &oy5, &oy6, &oy7, &oy8, &oy9, &oy10, &gx1, &gx2, &gx3, &gx4, &gx5, &gx6, &gx7, &gx8, &gx9, &gx10, &gy1, &gy2, &gy3, &gy4, &gy5, &gy6, &gy7, &gy8, &gy9, &gy10);
        //     close(fd8);
        // }

        int Ro = 10, Rg = 3, Rw = 3;      // Radios of obstacles efficeint repulsive force(Ro), Walls efficeint repulsive force(Rw) and efficient attract force (Rg)
        float no = 10.0, ng = 1, nw = 1; // the obstacles repulsive force gain (no), Walls repulsive force gain (nw) and attract force gain (ng)

        float od1 = 0.0, od2 = 0.0, od3 = 0.0, od4 = 0.0, od5 = 0.0, od6 = 0.0, od7 = 0.0, od8 = 0.0, od9 = 0.0, od10 = 0.0;
        float dx1 = ee_x - ox1, dx2 = ee_x - ox2, dx3 = ee_x - ox3, dx4 = ee_x - ox4, dx5 = ee_x - ox5, dx6 = ee_x - ox6, dx7 = ee_x - ox7, dx8 = ee_x - ox8, dx9 = ee_x - ox9, dx10 = ee_x - ox10;
        float dy1 = ee_y - oy1, dy2 = ee_y - oy2, dy3 = ee_y - oy3, dy4 = ee_y - oy4, dy5 = ee_y - oy5, dy6 = ee_y - oy6, dy7 = ee_y - oy7, dy8 = ee_y - oy8, dy9 = ee_y - oy9, dy10 = ee_y - oy10;

        // od1 = sqrt(pow(dx1, 2) + pow(dy1, 2));        // Calculate the drone distance to each obstacle
        // od2 = sqrt(pow(dx2, 2) + pow(dy2, 2));
        // od3 = sqrt(pow(dx3, 2) + pow(dy3, 2));
        // od4 = sqrt(pow(dx4, 2) + pow(dy4, 2));
        // od5 = sqrt(pow(dx5, 2) + pow(dy5, 2));        // Calculate the drone distance to each obstacle
        // od6 = sqrt(pow(dx6, 2) + pow(dy6, 2));
        // od7 = sqrt(pow(dx7, 2) + pow(dy7, 2));
        // od8 = sqrt(pow(dx8, 2) + pow(dy8, 2));
        // od9 = sqrt(pow(dx9, 2) + pow(dy9, 2));        // Calculate the drone distance to each obstacle
        // od10 = sqrt(pow(dx10, 2) + pow(dy10, 2));

        // // obstacle 1 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od1 < Ro)
        // {
        //     float of1=0.0;            
        //     float absdx1 = fabs (dx1);                      // Absolute distance number in x direction 
        //     float absdy1 = fabs (dy1);                      // Absolute distance number in y direction
            
        //     of1 = 0.5 * pow(((1.0 / od1) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox1 = (absdx1/(absdx1 + absdy1))*of1;          // The force in x direction 
        //     Foy1 = (absdy1/(absdx1 + absdy1))*of1;          // The force in y direction
        //     if(dx1 < 0)
        //     {
        //         Fox1 *= -1;
        //     }
        //     if(dy1 < 0)
        //     {
        //         Foy1 *= -1;
        //     }
        // }

        // // obstacle 2 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od2 < Ro)
        // {
        //     float of2=0.0;            
        //     float absdx2 = fabs (dx2);                      // Absolute distance number in x direction
        //     float absdy2 = fabs (dy2);                      // Absolute distance number in y direction
            
        //     of2 = 0.5 * pow(((1.0 / od2) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox2 = (absdx2/(absdx2 + absdy2))*of2;          // The force in x direction
        //     Foy2 = (absdy2/(absdx2 + absdy2))*of2;          // The force in y direction
        //     if(dx2 < 0)
        //     {
        //         Fox2 *= -1;
        //     }
        //     if(dy2 < 0)
        //     {
        //         Foy2 *= -1;
        //     }
        // }

        // // obstacle 3 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od3 < Ro)
        // {
        //     float of3=0.0;            
        //     float absdx3 = fabs (dx3);
        //     float absdy3 = fabs (dy3);
            
        //     of3 = 0.5 * pow(((1.0 / od3) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox3 = (absdx3/(absdx3 + absdy3))*of3;          // The force in x direction
        //     Foy3 = (absdy3/(absdx3 + absdy3))*of3;          // The force in y direction
        //     if(dx3 < 0)
        //     {
        //         Fox3 *= -1;
        //     }
        //     if(dy3 < 0)
        //     {
        //         Foy3 *= -1;
        //     }
        // }

        // // obstacle 4 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od4 < Ro)
        // {
        //     float of4=0.0;            
        //     float absdx4 = fabs (dx4);
        //     float absdy4 = fabs (dy4);
            
        //     of4 = 0.5 * pow(((1.0 / od4) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox4 = (absdx4/(absdx4 + absdy4))*of4;          // The force in x direction
        //     Foy4 = (absdy4/(absdx4 + absdy4))*of4;          // The force in y direction
        //     if(dx4 < 0)
        //     {
        //         Fox4 *= -1;
        //     }
        //     if(dy4 < 0)
        //     {
        //         Foy4 *= -1;
        //     }
        // }

        // // obstacle 5 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od5 < Ro)
        // {
        //     float of5=0.0;            
        //     float absdx5 = fabs (dx5);
        //     float absdy5 = fabs (dy5);
            
        //     of5 = 0.5 * pow(((1.0 / od5) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox5 = (absdx5/(absdx5 + absdy5))*of5;          // The force in x direction
        //     Foy5 = (absdy5/(absdx5 + absdy5))*of5;          // The force in y direction
        //     if(dx5 < 0)
        //     {
        //         Fox5 *= -1;
        //     }
        //     if(dy5 < 0)
        //     {
        //         Foy5 *= -1;
        //     }
        // }

        // // obstacle 6 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od6 < Ro)
        // {
        //     float of6=0.0;            
        //     float absdx6 = fabs (dx6);                      // Absolute distance number in x direction
        //     float absdy6 = fabs (dy6);                      // Absolute distance number in y direction
            
        //     of6 = 0.5 * pow(((1.0 / od6) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox6 = (absdx6/(absdx6 + absdy6))*of6;          // The force in x direction
        //     Foy6 = (absdy6/(absdx6 + absdy6))*of6;          // The force in y direction
        //     if(dx6 < 0)
        //     {
        //         Fox6 *= -1;
        //     }
        //     if(dy6 < 0)
        //     {
        //         Foy6 *= -1;
        //     }
        // }

        // // obstacle 7 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od7 < Ro)
        // {
        //     float of7=0.0;            
        //     float absdx7 = fabs (dx7);
        //     float absdy7 = fabs (dy7);
            
        //     of7 = 0.5 * pow(((1.0 / od7) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox7 = (absdx7/(absdx7 + absdy7))*of7;
        //     Foy7 = (absdy7/(absdx7 + absdy7))*of7;
        //     if(dx7 < 0)
        //     {
        //         Fox7 *= -1;
        //     }
        //     if(dy7 < 0)
        //     {
        //         Foy7 *= -1;
        //     }
        // }

        // // obstacle 8 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od8 < Ro)
        // {
        //     float of8=0.0;            
        //     float absdx8 = fabs (dx8);                      // Absolute distance number in x direction
        //     float absdy8 = fabs (dy8);                      // Absolute distance number in y direction
            
        //     of8 = 0.5 * pow(((1.0 / od8) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox8 = (absdx8/(absdx8 + absdy8))*of8;
        //     Foy8 = (absdy8/(absdx8 + absdy8))*of8;
        //     if(dx8 < 0)
        //     {
        //         Fox8 *= -1;
        //     }
        //     if(dy8 < 0)
        //     {
        //         Foy8 *= -1;
        //     }
        // }

        // // obstacle 9 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od9 < Ro)
        // {
        //     float of9=0.0;            
        //     float absdx9 = fabs (dx9);
        //     float absdy9 = fabs (dy9);
            
        //     of9 = 0.5 * pow(((1.0 / od9) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox9 = (absdx9/(absdx9 + absdy9))*of9;
        //     Foy9 = (absdy9/(absdx9 + absdy9))*of9;
        //     if(dx9 < 0)
        //     {
        //         Fox9 *= -1;
        //     }
        //     if(dy9 < 0)
        //     {
        //         Foy9 *= -1;
        //     }
        // }

        // // obstacle 10 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(od10 < Ro)
        // {
        //     float of10=0.0;            
        //     float absdx10 = fabs (dx10);                      // Absolute distance number in x direction
        //     float absdy10 = fabs (dy10);                      // Absolute distance number in y direction
            
        //     of10 = 0.5 * pow(((1.0 / od10) - (1.0 / Ro)), 2);
        //     usleep(100);
        //     Fox10 = (absdx10/(absdx10 + absdy10))*of10;
        //     Foy10 = (absdy10/(absdx10 + absdy10))*of10;
        //     if(dx10 < 0)
        //     {
        //         Fox10 *= -1;
        //     }
        //     if(dy10 < 0)
        //     {
        //         Foy10 *= -1;
        //     }
        // }

        float Flbx=0.0, Frbx=0.0, Ftby=0.0, Fbby=0.0;                   // lb: left border, rb: right border, tb: top border, bb: buttom border, 

        // Left border repulsive force calculator if the drone is close enough the force will be applied to drone
        if(ee_x < Rw)
        {
            Flbx = 0.5 * pow(((1.0 / ee_x) - (1.0 / Rw)), 2);
            usleep(100);
        }
        // Right border repulsive force calculator if the drone is close enough the force will be applied to drone
        else if((COURT_X_LIM - ee_x) < Rw)
        {
            Frbx = 0.5 * pow(((1.0 / (COURT_X_LIM - ee_x)) - (1.0 / Rw)), 2);
            usleep(100);
        }
        // Top border repulsive force calculator if the drone is close enough the force will be applied to drone
        if(ee_y < Rw)
        {
            Ftby = 0.5 * pow(((1.0 / ee_y) - (1.0 / Rw)), 2);
            usleep(100);
        }
        // Right border repulsive force calculator if the drone is close enough the force will be applied to drone
        else if((COURT_Y_LIM - ee_y) < Rw)
        {
            Fbby = 0.5 * pow(((1.0 / (COURT_Y_LIM - ee_y)) - (1.0 / Rw)), 2);
            usleep(100);
        }

        float gd1 = 0.0, gd2 = 0.0, gd3 = 0.0, gd4 = 0.0, gd5 = 0.0, gd6 = 0.0, gd7 = 0.0, gd8 = 0.0, gd9 = 0.0, gd10 = 0.0;
        float dgx1 = ee_x - gx1, dgx2 = ee_x - gx2, dgx3 = ee_x - gx3, dgx4 = ee_x - gx4, dgx5 = ee_x - gx5, dgx6 = ee_x - gx6, dgx7 = ee_x - gx7, dgx8 = ee_x - gx8, dgx9 = ee_x - gx9, dgx10 = ee_x - gx10;
        float dgy1 = ee_y - gy1, dgy2 = ee_y - gy2, dgy3 = ee_y - gy3, dgy4 = ee_y - gy4, dgy5 = ee_y - gy5, dgy6 = ee_y - gy6, dgy7 = ee_y - gy7, dgy8 = ee_y - gy8, dgy9 = ee_y - gy9, dgy10 = ee_y - gy10;
        float fgMax = 3;

        // gd1 = sqrt(pow(dgx1, 2) + pow(dgy1, 2));        // Calculate the drone distance to each goal
        // gd2 = sqrt(pow(dgx2, 2) + pow(dgy2, 2));
        // gd3 = sqrt(pow(dgx3, 2) + pow(dgy3, 2));
        // gd4 = sqrt(pow(dgx4, 2) + pow(dgy4, 2));
        // gd5 = sqrt(pow(dgx5, 2) + pow(dgy5, 2));        // Calculate the drone distance to each goal
        // gd6 = sqrt(pow(dgx6, 2) + pow(dgy6, 2));
        // gd7 = sqrt(pow(dgx7, 2) + pow(dgy7, 2));
        // gd8 = sqrt(pow(dgx8, 2) + pow(dgy8, 2));
        // gd9 = sqrt(pow(dgx9, 2) + pow(dgy9, 2));        // Calculate the drone distance to each goal
        // gd10 = sqrt(pow(dgx10, 2) + pow(dgy10, 2));

        // // goal 1 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal1){
        //     if(gd1 < Rg)
        //     {
        //         float gf1=0.0;            
        //         float absdgx1 = fabs (dgx1);                      // Absolute distance number in x direction
        //         float absdgy1 = fabs (dgy1);                      // Absolute distance number in y direction
                
        //         gf1 = 0.5 * pow(((1.0 / gd1) - (1.0 / Rg)), 2);
        //         if(gf1 > fgMax)
        //         {
        //             gf1 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx1 = (absdgx1/(absdgx1 + absdgy1))*gf1;
        //         Fgy1 = (absdgy1/(absdgx1 + absdgy1))*gf1;
        //         if(dgx1 > 0)
        //         {
        //             Fgx1 *= -1;
        //         }
        //         if(dgy1 > 0)
        //         {
        //             Fgy1 *= -1;
        //         }
        //     }
        // }

        // // goal 2 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal2){
        //     if(gd2 < Rg)
        //     {
        //         float gf2=0.0;            
        //         float absdgx2 = fabs (dgx2);
        //         float absdgy2 = fabs (dgy2);
                
        //         gf2 = 0.5 * pow(((1.0 / gd2) - (1.0 / Rg)), 2);
        //         if(gf2 > fgMax)
        //         {
        //             gf2 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx2 = (absdgx2/(absdgx2 + absdgy2))*gf2;          // The force in x direction
        //         Fgy2 = (absdgy2/(absdgx2 + absdgy2))*gf2;          // The force in y direction
        //         if(dgx2 > 0)
        //         {
        //             Fgx2 *= -1;
        //         }
        //         if(dgy2 > 0)
        //         {
        //             Fgy2 *= -1;
        //         }
        //     }
        // }
            
        // // goal 3 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal3){
        //     if(gd3 < Rg)
        //     {
        //         float gf3=0.0;            
        //         float absdgx3 = fabs (dgx3);                      // Absolute distance number in x direction
        //         float absdgy3 = fabs (dgy3);                      // Absolute distance number in y direction
                
        //         gf3 = 0.5 * pow(((1.0 / gd3) - (1.0 / Rg)), 2);
        //         if(gf3 > fgMax)
        //         {
        //             gf3 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx3 = (absdgx3/(absdgx3 + absdgy3))*gf3;
        //         Fgy3 = (absdgy3/(absdgx3 + absdgy3))*gf3;
        //         if(dgx3 > 0)
        //         {
        //             Fgx3 *= -1;
        //         }
        //         if(dgy3 > 0)
        //         {
        //             Fgy3 *= -1;
        //         }
        //     }
        // }
            
        // // goal 4 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal4){
        //     if(gd4 < Rg)
        //     {
        //         float gf4=0.0;            
        //         float absdgx4 = fabs (dgx4);
        //         float absdgy4 = fabs (dgy4);
                
        //         gf4 = 0.5 * pow(((1.0 / gd4) - (1.0 / Rg)), 2);
        //         if(gf4 > fgMax)
        //         {
        //             gf4 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx4 = (absdgx4/(absdgx4 + absdgy4))*gf4;          // The force in x direction
        //         Fgy4 = (absdgy4/(absdgx4 + absdgy4))*gf4;          // The force in y direction
        //         if(dgx4 > 0)
        //         {
        //             Fgx4 *= -1;
        //         }
        //         if(dgy4 > 0)
        //         {
        //             Fgy4 *= -1;
        //         }
        //     }
        // }
            
        // // goal 5 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal5){
        //     if(gd5 < Rg)
        //     {
        //         float gf5=0.0;            
        //         float absdgx5 = fabs (dgx5);                      // Absolute distance number in x direction
        //         float absdgy5 = fabs (dgy5);                      // Absolute distance number in y direction
                
        //         gf5 = 0.5 * pow(((1.0 / gd5) - (1.0 / Rg)), 2);
        //         if(gf5 > fgMax)
        //         {
        //             gf5 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx5 = (absdgx5/(absdgx5 + absdgy5))*gf5;
        //         Fgy5 = (absdgy5/(absdgx5 + absdgy5))*gf5;
        //         if(dgx5 > 0)
        //         {
        //             Fgx5 *= -1;
        //         }
        //         if(dgy5 > 0)
        //         {
        //             Fgy5 *= -1;
        //         }
        //     }
        // }
            
        // // goal 6 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal6){
        //     if(gd6 < Rg)
        //     {
        //         float gf6=0.0;            
        //         float absdgx6 = fabs (dgx6);
        //         float absdgy6 = fabs (dgy6);
                
        //         gf6 = 0.5 * pow(((1.0 / gd6) - (1.0 / Rg)), 2);
        //         if(gf6 > fgMax)
        //         {
        //             gf6 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx6 = (absdgx6/(absdgx6 + absdgy6))*gf6;          // The force in x direction
        //         Fgy6 = (absdgy6/(absdgx6 + absdgy6))*gf6;          // The force in y direction
        //         if(dgx6 > 0)
        //         {
        //             Fgx6 *= -1;
        //         }
        //         if(dgy6 > 0)
        //         {
        //             Fgy6 *= -1;
        //         }
        //     }
        // }
            
        // // goal 7 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal7){
        //     if(gd7 < Rg)
        //     {
        //         float gf7=0.0;            
        //         float absdgx7 = fabs (dgx7);
        //         float absdgy7 = fabs (dgy7);
                
        //         gf7 = 0.5 * pow(((1.0 / gd7) - (1.0 / Rg)), 2);
        //         if(gf7 > fgMax)
        //         {
        //             gf7 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx7 = (absdgx7/(absdgx7 + absdgy7))*gf7;
        //         Fgy7 = (absdgy7/(absdgx7 + absdgy7))*gf7;
        //         if(dgx7 > 0)
        //         {
        //             Fgx7 *= -1;
        //         }
        //         if(dgy7 > 0)
        //         {
        //             Fgy7 *= -1;
        //         }
        //     }
        // }
            
        // // goal 8 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal8){
        //     if(gd8 < Rg)
        //     {
        //         float gf8=0.0;            
        //         float absdgx8 = fabs (dgx8);                      // Absolute distance number in x direction
        //         float absdgy8 = fabs (dgy8);                      // Absolute distance number in y direction
                
        //         gf8 = 0.5 * pow(((1.0 / gd8) - (1.0 / Rg)), 2);
        //         if(gf8 > fgMax)
        //         {
        //             gf8 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx8 = (absdgx8/(absdgx8 + absdgy8))*gf8;          // The force in x direction
        //         Fgy8 = (absdgy8/(absdgx8 + absdgy8))*gf8;          // The force in y direction
        //         if(dgx8 > 0)
        //         {
        //             Fgx8 *= -1;
        //         }
        //         if(dgy8 > 0)
        //         {
        //             Fgy8 *= -1;
        //         }
        //     }
        // }
            
        // // goal 9 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal9){
        //     if(gd9 < Rg)
        //     {
        //         float gf9=0.0;            
        //         float absdgx9 = fabs (dgx9);
        //         float absdgy9 = fabs (dgy9);
                
        //         gf9 = 0.5 * pow(((1.0 / gd9) - (1.0 / Rg)), 2);
        //         if(gf9 > fgMax)
        //         {
        //             gf9 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx9 = (absdgx9/(absdgx9 + absdgy9))*gf9;          // The force in x direction
        //         Fgy9 = (absdgy9/(absdgx9 + absdgy9))*gf9;          // The force in y direction
        //         if(dgx9 > 0)
        //         {
        //             Fgx9 *= -1;
        //         }
        //         if(dgy9 > 0)
        //         {
        //             Fgy9 *= -1;
        //         }
        //     }
        // }
            
        // // goal 10 repulsive force calculator if the drone is close enough the force will be applied to drone
        // if(!reachedGoal10){
        //     if(gd10 < Rg)
        //     {
        //         float gf10=0.0;            
        //         float absdgx10 = fabs (dgx10);                      // Absolute distance number in x direction
        //         float absdgy10 = fabs (dgy10);                      // Absolute distance number in y direction
                
        //         gf10 = 0.5 * pow(((1.0 / gd10) - (1.0 / Rg)), 2);
        //         if(gf10 > fgMax)
        //         {
        //             gf10 = fgMax;
        //         }
        //         usleep(100);
        //         Fgx10 = (absdgx10/(absdgx10 + absdgy10))*gf10;
        //         Fgy10 = (absdgy10/(absdgx10 + absdgy10))*gf10;
        //         if(dgx10 > 0)
        //         {
        //             Fgx10 *= -1;
        //         }
        //         if(dgy10 > 0)
        //         {
        //             Fgy10 *= -1;
        //         }
        //     }
        // }

        // We add all the forces together
        Fx = (no * (Fox1+Fox2+Fox3+Fox4+Fox5+Fox6+Fox7+Fox8+Fox9+Fox10))+(ng * (Fgx1+Fgx2+Fgx3+Fgx4+Fgx5+Fgx6+Fgx7+Fgx8+Fgx9+Fgx10))+(nw * (Flbx-Frbx));
        Fy = (no * (Foy1+Foy2+Foy3+Foy4+Foy5+Foy6+Foy7+Foy8+Foy9+Foy10))+(ng * (Fgy1+Fgy2+Fgy3+Fgy4+Fgy5+Fgy6+Fgy7+Fgy8+Fgy9+Fgy10))+(nw * (Ftby-Fbby));

        if (Fx > 50){Fx = 50;}else if (Fx < -50){Fx = -50;}
        if (Fy > 50){Fy = 50;}else if (Fy < -50){Fy = -50;}

        // We add the calculated force to the input force
        fx += Fx;
        fy += Fy;
        usleep(100);

        // We need to include the air force in order to prevent letting the drone move for ever, so we multiply the drag ratio to total force
        fx *= D;
        fy *= D;

        // According to f=ma ==> a=f/m ===(m=1)==> a=f so we can say for each key press we apply a=1 (m/s).
        // we know a=(delta)v so we can say when we press any key the velocity increase 1m/s in that direction.
        vx = fx;
        vy = fy;

        if (fabs(vx) < 0.01){vx = 0.0;}
        if (fabs(vy) < 0.01){vy = 0.0;}

        usleep(100);

        ee_x += (vx/100);
        ee_y += (vy/100);

        // Checks for horizontal axis
        if(ee_x <= 0) {
            ee_x = 0 ;
        }
        else if(ee_x >= COURT_X_LIM) {
            ee_x = COURT_X_LIM-1;
        }
    
        // Checks for vertical axis
        if(ee_y <= 0) {
            ee_y = 0 ;
        }
        else if(ee_y >= COURT_Y_LIM) {
            ee_y = COURT_Y_LIM-1;
        }

        // // check if the ee is close enough to goals
        // if (gd1 < 1)
        // {
        //     reachedGoal1 = 1;              // the drone reached first goal
        // }
        // if (gd2 < 0.5)
        // {
        //     reachedGoal2 = 1;              // the drone reached 2nd goal
        // }
        // if (gd3 < 0.5)
        // {
        //     reachedGoal3 = 1;              // the drone reached 3rd goal
        // }
        // if (gd4 < 0.5)
        // {
        //     reachedGoal4 = 1;              // the drone reached 4th goal
        // }
        // if (gd5 < 0.5)
        // {
        //     reachedGoal5 = 1;              // the drone reached 5th goal
        // }
        // if (gd6 < 0.5)
        // {
        //     reachedGoal6 = 1;              // the drone reached 6th goal
        // }
        // if (gd7 < 0.5)
        // {
        //     reachedGoal7 = 1;              // the drone reached 7th goal
        // }
        // if (gd8 < 0.5)
        // {
        //     reachedGoal8 = 1;              // the drone reached 8th goal
        // }
        // if (gd9 < 0.5)
        // {
        //     reachedGoal9 = 1;              // the drone reached 9th goal
        // }
        // if (gd10 < 0.5)
        // {
        //     reachedGoal10 = 1;              // the drone reached 10th goal
        // }

        // fd10 = open(myfifo10,O_WRONLY);     // Let input processor know if any goals reached and stop printing them
        // if (fd10 == -1) {
        //     perror("Error opening FIFO10");
        // }
        // sprintf(str10, format_string10, reachedGoal1, reachedGoal2, reachedGoal3, reachedGoal4, reachedGoal5, reachedGoal6, reachedGoal7, reachedGoal8, reachedGoal9, reachedGoal10);
        // write(fd10, str10, strlen(str10)+1);
        // close(fd10);

        usleep(1700);

        if(reachedAllTheGoals)
        {
            reachedAllTheGoals = 0;
        }      

        // Check if the drone has velocity and send the signal to watchdog
        if (vx!=0 || vy!=0) {
            computation_in_progress = 1;
        } else {
            computation_in_progress = 0;
        }

        // fd13 = open(myfifo13,O_WRONLY | O_NONBLOCK);
        // // if (fd13 == -1) {
        // //     perror("Error opening FIFO13");
        // // }
        // sprintf(str13, format_string13, computation_in_progress);
        // write(fd13, str13, strlen(str13)+1);
        // close(fd13);
    }
    // Cleanup
    endwin();

    return 0;
}
// 0.003000 s



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483