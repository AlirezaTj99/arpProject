#include "./../include/force.h"

int main(){

    // Initialize Shared Memory
    int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sleep(1);
    while(TRUE)
    {
        shared_data->x = ee_x;
        shared_data->y = ee_y;
        shared_data->Vx = vx;
        shared_data->Vy = vy;

        if(shared_data->xForceIncrease)
        {
            fx++;
            usleep(1000);
            shared_data->xForceIncrease = 0;
        }
        else if (shared_data->xForceDecrease)
        {
            fx--;
            usleep(1000);
            shared_data->xForceDecrease = 0;
        }
        if (shared_data->yForceIncrease)
        {
            fy++;
            usleep(1000);
            shared_data->yForceIncrease = 0;
        }
        else if (shared_data->yForceDecrease)
        {
            fy--;
            usleep(1000);
            shared_data->yForceDecrease = 0;
        }
        if (shared_data->zeroForce)
        {
            fx = 0;
            fy = 0;
            usleep(1000);
            shared_data->zeroForce = 0;
        }

        int x1, x2, x3, x4, x5, x6, x7, x8, x9, x10; float Fx=0.0, Fx1=0.0, Fx2=0.0, Fx3=0.0, Fx4=0.0, Fx5=0.0, Fx6=0.0, Fx7=0.0, Fx8=0.0, Fx9=0.0, Fx10=0.0;
        int y1, y2, y3, y4, y5, y6, y7, y8, y9, y10; float Fy=0.0, Fy1=0.0, Fy2=0.0, Fy3=0.0, Fy4=0.0, Fy5=0.0, Fy6=0.0, Fy7=0.0, Fy8=0.0, Fy9=0.0, Fy10=0.0;

        int Ro = 10, Rg = 3;                  // Radios of efficeint repulsive force(Ro) and efficient attract force (Rg)
        float no = 10.0, ng = 1;              // the repulsive force gain (no) and attract force gain (ng)

        // Import obstacle coordinates
        x1 = shared_data->ox1 ;
        x2 = shared_data->ox2 ;
        x3 = shared_data->ox3 ;
        x4 = shared_data->ox4 ;
        x5 = shared_data->ox5 ;
        x6 = shared_data->ox6 ;
        x7 = shared_data->ox7 ;
        x8 = shared_data->ox8 ;
        x9 = shared_data->ox9 ;
        x10 = shared_data->ox10 ;
        y1 = shared_data->oy1 ;
        y2 = shared_data->oy2 ;
        y3 = shared_data->oy3 ;
        y4 = shared_data->oy4 ;
        y5 = shared_data->oy5 ;
        y6 = shared_data->oy6 ;
        y7 = shared_data->oy7 ;
        y8 = shared_data->oy8 ;
        y9 = shared_data->oy9 ;
        y10 = shared_data->oy10 ;

        usleep(500);

        float od1 = 0.0, od2 = 0.0, od3 = 0.0, od4 = 0.0, od5 = 0.0, od6 = 0.0, od7 = 0.0, od8 = 0.0, od9 = 0.0, od10 = 0.0;
        float dx1 = ee_x - x1, dx2 = ee_x - x2, dx3 = ee_x - x3, dx4 = ee_x - x4, dx5 = ee_x - x5, dx6 = ee_x - x6, dx7 = ee_x - x7, dx8 = ee_x - x8, dx9 = ee_x - x9, dx10 = ee_x - x10;
        float dy1 = ee_y - y1, dy2 = ee_y - y2, dy3 = ee_y - y3, dy4 = ee_y - y4, dy5 = ee_y - y5, dy6 = ee_y - y6, dy7 = ee_y - y7, dy8 = ee_y - y8, dy9 = ee_y - y9, dy10 = ee_y - y10;

        od1 = sqrt(pow(dx1, 2) + pow(dy1, 2));
        od2 = sqrt(pow(dx2, 2) + pow(dy2, 2));
        od3 = sqrt(pow(dx3, 2) + pow(dy3, 2));
        od4 = sqrt(pow(dx4, 2) + pow(dy4, 2));
        od5 = sqrt(pow(dx5, 2) + pow(dy5, 2));
        od6 = sqrt(pow(dx6, 2) + pow(dy6, 2));
        od7 = sqrt(pow(dx7, 2) + pow(dy7, 2));
        od8 = sqrt(pow(dx8, 2) + pow(dy8, 2));
        od9 = sqrt(pow(dx9, 2) + pow(dy9, 2));
        od10 = sqrt(pow(dx10, 2) + pow(dy10, 2));

        
        usleep(500);

        // obstacle 1 repulsive force calculator
        if(od1 < Ro)
        {
            float of1=0.0;            
            float absdx1 = fabs (dx1);
            float absdy1 = fabs (dy1);
            
            of1 = 0.5 * pow(((1.0 / od1) - (1.0 / Ro)), 2);
            usleep(100);
            Fx1 = (absdx1/(absdx1 + absdy1))*of1;
            Fy1 = (absdy1/(absdx1 + absdy1))*of1;
            if(dx1 < 0)
            {
                Fx1 *= -1;
            }
            if(dy1 < 0)
            {
                Fy1 *= -1;
            }
        }

        // obstacle 2 repulsive force calculator
        if(od2 < Ro)
        {
            float of2=0.0;            
            float absdx2 = fabs (dx2);
            float absdy2 = fabs (dy2);
            
            of2 = 0.5 * pow(((1.0 / od2) - (1.0 / Ro)), 2);
            usleep(100);
            Fx2 = (absdx2/(absdx2 + absdy2))*of2;
            Fy2 = (absdy2/(absdx2 + absdy2))*of2;
            if(dx2 < 0)
            {
                Fx2 *= -1;
            }
            if(dy2 < 0)
            {
                Fy2 *= -1;
            }
        }

        // obstacle 3 repulsive force calculator
        if(od3 < Ro)
        {
            float of3=0.0;            
            float absdx3 = fabs (dx3);
            float absdy3 = fabs (dy3);
            
            of3 = 0.5 * pow(((1.0 / od3) - (1.0 / Ro)), 2);
            usleep(100);
            Fx3 = (absdx3/(absdx3 + absdy3))*of3;
            Fy3 = (absdy3/(absdx3 + absdy3))*of3;
            if(dx3 < 0)
            {
                Fx3 *= -1;
            }
            if(dy3 < 0)
            {
                Fy3 *= -1;
            }
        }

        // obstacle 4 repulsive force calculator
        if(od4 < Ro)
        {
            float of4=0.0;            
            float absdx4 = fabs (dx4);
            float absdy4 = fabs (dy4);
            
            of4 = 0.5 * pow(((1.0 / od4) - (1.0 / Ro)), 2);
            usleep(100);
            Fx4 = (absdx4/(absdx4 + absdy4))*of4;
            Fy4 = (absdy4/(absdx4 + absdy4))*of4;
            if(dx4 < 0)
            {
                Fx4 *= -1;
            }
            if(dy4 < 0)
            {
                Fy4 *= -1;
            }
        }

        // obstacle 5 repulsive force calculator
        if(od5 < Ro)
        {
            float of5=0.0;            
            float absdx5 = fabs (dx5);
            float absdy5 = fabs (dy5);
            
            of5 = 0.5 * pow(((1.0 / od5) - (1.0 / Ro)), 2);
            usleep(100);
            Fx5 = (absdx5/(absdx5 + absdy5))*of5;
            Fy5 = (absdy5/(absdx5 + absdy5))*of5;
            if(dx5 < 0)
            {
                Fx5 *= -1;
            }
            if(dy5 < 0)
            {
                Fy5 *= -1;
            }
        }

        // obstacle 6 repulsive force calculator
        if(od6 < Ro)
        {
            float of6=0.0;            
            float absdx6 = fabs (dx6);
            float absdy6 = fabs (dy6);
            
            of6 = 0.5 * pow(((1.0 / od6) - (1.0 / Ro)), 2);
            usleep(100);
            Fx6 = (absdx6/(absdx6 + absdy6))*of6;
            Fy6 = (absdy6/(absdx6 + absdy6))*of6;
            if(dx6 < 0)
            {
                Fx6 *= -1;
            }
            if(dy6 < 0)
            {
                Fy6 *= -1;
            }
        }

        // obstacle 7 repulsive force calculator
        if(od7 < Ro)
        {
            float of7=0.0;            
            float absdx7 = fabs (dx7);
            float absdy7 = fabs (dy7);
            
            of7 = 0.5 * pow(((1.0 / od7) - (1.0 / Ro)), 2);
            usleep(100);
            Fx7 = (absdx7/(absdx7 + absdy7))*of7;
            Fy7 = (absdy7/(absdx7 + absdy7))*of7;
            if(dx7 < 0)
            {
                Fx7 *= -1;
            }
            if(dy7 < 0)
            {
                Fy7 *= -1;
            }
        }

        // obstacle 8 repulsive force calculator
        if(od8 < Ro)
        {
            float of8=0.0;            
            float absdx8 = fabs (dx8);
            float absdy8 = fabs (dy8);
            
            of8 = 0.5 * pow(((1.0 / od8) - (1.0 / Ro)), 2);
            usleep(100);
            Fx8 = (absdx8/(absdx8 + absdy8))*of8;
            Fy8 = (absdy8/(absdx8 + absdy8))*of8;
            if(dx8 < 0)
            {
                Fx8 *= -1;
            }
            if(dy8 < 0)
            {
                Fy8 *= -1;
            }
        }

        // obstacle 9 repulsive force calculator
        if(od9 < Ro)
        {
            float of9=0.0;            
            float absdx9 = fabs (dx9);
            float absdy9 = fabs (dy9);
            
            of9 = 0.5 * pow(((1.0 / od9) - (1.0 / Ro)), 2);
            usleep(100);
            Fx9 = (absdx9/(absdx9 + absdy9))*of9;
            Fy9 = (absdy9/(absdx9 + absdy9))*of9;
            if(dx9 < 0)
            {
                Fx9 *= -1;
            }
            if(dy9 < 0)
            {
                Fy9 *= -1;
            }
        }

        // obstacle 10 repulsive force calculator
        if(od10 < Ro)
        {
            float of10=0.0;            
            float absdx10 = fabs (dx10);
            float absdy10 = fabs (dy10);
            
            of10 = 0.5 * pow(((1.0 / od10) - (1.0 / Ro)), 2);
            usleep(100);
            Fx10 = (absdx10/(absdx10 + absdy10))*of10;
            Fy10 = (absdy10/(absdx10 + absdy10))*of10;
            if(dx10 < 0)
            {
                Fx10 *= -1;
            }
            if(dy10 < 0)
            {
                Fy10 *= -1;
            }
        }

        int gx1, gx2, gx3, gx4, gx5, gx6, gx7, gx8, gx9, gx10; float Fgx1=0.0, Fgx2=0.0, Fgx3=0.0, Fgx4=0.0, Fgx5=0.0, Fgx6=0.0, Fgx7=0.0, Fgx8=0.0, Fgx9=0.0, Fgx10=0.0;
        int gy1, gy2, gy3, gy4, gy5, gy6, gy7, gy8, gy9, gy10; float Fgy1=0.0, Fgy2=0.0, Fgy3=0.0, Fgy4=0.0, Fgy5=0.0, Fgy6=0.0, Fgy7=0.0, Fgy8=0.0, Fgy9=0.0, Fgy10=0.0;
        
        // Import obstacle coordinates
        gx1 = shared_data->gx1 ;
        gx2 = shared_data->gx2 ;
        gx3 = shared_data->gx3 ;
        gx4 = shared_data->gx4 ;
        gx5 = shared_data->gx5 ;
        gx6 = shared_data->gx6 ;
        gx7 = shared_data->gx7 ;
        gx8 = shared_data->gx8 ;
        gx9 = shared_data->gx9 ;
        gx10 = shared_data->gx10 ;
        gy1 = shared_data->gy1 ;
        gy2 = shared_data->gy2 ;
        gy3 = shared_data->gy3 ;
        gy4 = shared_data->gy4 ;
        gy5 = shared_data->gy5 ;
        gy6 = shared_data->gy6 ;
        gy7 = shared_data->gy7 ;
        gy8 = shared_data->gy8 ;
        gy9 = shared_data->gy9 ;
        gy10 = shared_data->gy10 ;

        float gd1 = 0.0, gd2 = 0.0, gd3 = 0.0, gd4 = 0.0, gd5 = 0.0, gd6 = 0.0, gd7 = 0.0, gd8 = 0.0, gd9 = 0.0, gd10 = 0.0;
        float dgx1 = ee_x - gx1, dgx2 = ee_x - gx2, dgx3 = ee_x - gx3, dgx4 = ee_x - gx4, dgx5 = ee_x - gx5, dgx6 = ee_x - gx6, dgx7 = ee_x - gx7, dgx8 = ee_x - gx8, dgx9 = ee_x - gx9, dgx10 = ee_x - gx10;
        float dgy1 = ee_y - gy1, dgy2 = ee_y - gy2, dgy3 = ee_y - gy3, dgy4 = ee_y - gy4, dgy5 = ee_y - gy5, dgy6 = ee_y - gy6, dgy7 = ee_y - gy7, dgy8 = ee_y - gy8, dgy9 = ee_y - gy9, dgy10 = ee_y - gy10;
        float fgMax = 3;

        gd1 = sqrt(pow(dgx1, 2) + pow(dgy1, 2));
        gd2 = sqrt(pow(dgx2, 2) + pow(dgy2, 2));
        gd3 = sqrt(pow(dgx3, 2) + pow(dgy3, 2));
        gd4 = sqrt(pow(dgx4, 2) + pow(dgy4, 2));
        gd5 = sqrt(pow(dgx5, 2) + pow(dgy5, 2));
        gd6 = sqrt(pow(dgx6, 2) + pow(dgy6, 2));
        gd7 = sqrt(pow(dgx7, 2) + pow(dgy7, 2));
        gd8 = sqrt(pow(dgx8, 2) + pow(dgy8, 2));
        gd9 = sqrt(pow(dgx9, 2) + pow(dgy9, 2));
        gd10 = sqrt(pow(dgx10, 2) + pow(dgy10, 2));

        // goal 1 repulsive force calculator
        if(gd1 < Rg)
        {
            float gf1=0.0;            
            float absdgx1 = fabs (dgx1);
            float absdgy1 = fabs (dgy1);
            
            gf1 = 0.5 * pow(((1.0 / gd1) - (1.0 / Rg)), 2);
            if(gf1 > fgMax)
            {
                gf1 = fgMax;
            }
            usleep(100);
            Fgx1 = (absdgx1/(absdgx1 + absdgy1))*gf1;
            Fgy1 = (absdgy1/(absdgx1 + absdgy1))*gf1;
            if(dgx1 > 0)
            {
                Fgx1 *= -1;
            }
            if(dgy1 > 0)
            {
                Fgy1 *= -1;
            }
        }

        // goal 2 repulsive force calculator
        if(gd2 < Rg)
        {
            float gf2=0.0;            
            float absdgx2 = fabs (dgx2);
            float absdgy2 = fabs (dgy2);
            
            gf2 = 0.5 * pow(((1.0 / gd2) - (1.0 / Rg)), 2);
            if(gf2 > fgMax)
            {
                gf2 = fgMax;
            }
            usleep(100);
            Fgx2 = (absdgx2/(absdgx2 + absdgy2))*gf2;
            Fgy2 = (absdgy2/(absdgx2 + absdgy2))*gf2;
            if(dgx2 > 0)
            {
                Fgx2 *= -1;
            }
            if(dgy2 > 0)
            {
                Fgy2 *= -1;
            }
        }
        
        // goal 3 repulsive force calculator
        if(gd3 < Rg)
        {
            float gf3=0.0;            
            float absdgx3 = fabs (dgx3);
            float absdgy3 = fabs (dgy3);
            
            gf3 = 0.5 * pow(((1.0 / gd3) - (1.0 / Rg)), 2);
            if(gf3 > fgMax)
            {
                gf3 = fgMax;
            }
            usleep(100);
            Fgx3 = (absdgx3/(absdgx3 + absdgy3))*gf3;
            Fgy3 = (absdgy3/(absdgx3 + absdgy3))*gf3;
            if(dgx3 > 0)
            {
                Fgx3 *= -1;
            }
            if(dgy3 > 0)
            {
                Fgy3 *= -1;
            }
        }
        
        // goal 4 repulsive force calculator
        if(gd4 < Rg)
        {
            float gf4=0.0;            
            float absdgx4 = fabs (dgx4);
            float absdgy4 = fabs (dgy4);
            
            gf4 = 0.5 * pow(((1.0 / gd4) - (1.0 / Rg)), 2);
            if(gf4 > fgMax)
            {
                gf4 = fgMax;
            }
            usleep(100);
            Fgx4 = (absdgx4/(absdgx4 + absdgy4))*gf4;
            Fgy4 = (absdgy4/(absdgx4 + absdgy4))*gf4;
            if(dgx4 > 0)
            {
                Fgx4 *= -1;
            }
            if(dgy4 > 0)
            {
                Fgy4 *= -1;
            }
        }
        
        // goal 5 repulsive force calculator
        if(gd5 < Rg)
        {
            float gf5=0.0;            
            float absdgx5 = fabs (dgx5);
            float absdgy5 = fabs (dgy5);
            
            gf5 = 0.5 * pow(((1.0 / gd5) - (1.0 / Rg)), 2);
            if(gf5 > fgMax)
            {
                gf5 = fgMax;
            }
            usleep(100);
            Fgx5 = (absdgx5/(absdgx5 + absdgy5))*gf5;
            Fgy5 = (absdgy5/(absdgx5 + absdgy5))*gf5;
            if(dgx5 > 0)
            {
                Fgx5 *= -1;
            }
            if(dgy5 > 0)
            {
                Fgy5 *= -1;
            }
        }
        
        // goal 6 repulsive force calculator
        if(gd6 < Rg)
        {
            float gf6=0.0;            
            float absdgx6 = fabs (dgx6);
            float absdgy6 = fabs (dgy6);
            
            gf6 = 0.5 * pow(((1.0 / gd6) - (1.0 / Rg)), 2);
            if(gf6 > fgMax)
            {
                gf6 = fgMax;
            }
            usleep(100);
            Fgx6 = (absdgx6/(absdgx6 + absdgy6))*gf6;
            Fgy6 = (absdgy6/(absdgx6 + absdgy6))*gf6;
            if(dgx6 > 0)
            {
                Fgx6 *= -1;
            }
            if(dgy6 > 0)
            {
                Fgy6 *= -1;
            }
        }
        
        // goal 7 repulsive force calculator
        if(gd7 < Rg)
        {
            float gf7=0.0;            
            float absdgx7 = fabs (dgx7);
            float absdgy7 = fabs (dgy7);
            
            gf7 = 0.5 * pow(((1.0 / gd7) - (1.0 / Rg)), 2);
            if(gf7 > fgMax)
            {
                gf7 = fgMax;
            }
            usleep(100);
            Fgx7 = (absdgx7/(absdgx7 + absdgy7))*gf7;
            Fgy7 = (absdgy7/(absdgx7 + absdgy7))*gf7;
            if(dgx7 > 0)
            {
                Fgx7 *= -1;
            }
            if(dgy7 > 0)
            {
                Fgy7 *= -1;
            }
        }
        
        // goal 8 repulsive force calculator
        if(gd8 < Rg)
        {
            float gf8=0.0;            
            float absdgx8 = fabs (dgx8);
            float absdgy8 = fabs (dgy8);
            
            gf8 = 0.5 * pow(((1.0 / gd8) - (1.0 / Rg)), 2);
            if(gf8 > fgMax)
            {
                gf8 = fgMax;
            }
            usleep(100);
            Fgx8 = (absdgx8/(absdgx8 + absdgy8))*gf8;
            Fgy8 = (absdgy8/(absdgx8 + absdgy8))*gf8;
            if(dgx8 > 0)
            {
                Fgx8 *= -1;
            }
            if(dgy8 > 0)
            {
                Fgy8 *= -1;
            }
        }
        
        // goal 9 repulsive force calculator
        if(gd9 < Rg)
        {
            float gf9=0.0;            
            float absdgx9 = fabs (dgx9);
            float absdgy9 = fabs (dgy9);
            
            gf9 = 0.5 * pow(((1.0 / gd9) - (1.0 / Rg)), 2);
            if(gf9 > fgMax)
            {
                gf9 = fgMax;
            }
            usleep(100);
            Fgx9 = (absdgx9/(absdgx9 + absdgy9))*gf9;
            Fgy9 = (absdgy9/(absdgx9 + absdgy9))*gf9;
            if(dgx9 > 0)
            {
                Fgx9 *= -1;
            }
            if(dgy9 > 0)
            {
                Fgy9 *= -1;
            }
        }
        
        // goal 10 repulsive force calculator
        if(gd10 < Rg)
        {
            float gf10=0.0;            
            float absdgx10 = fabs (dgx10);
            float absdgy10 = fabs (dgy10);
            
            gf10 = 0.5 * pow(((1.0 / gd10) - (1.0 / Rg)), 2);
            if(gf10 > fgMax)
            {
                gf10 = fgMax;
            }
            usleep(100);
            Fgx10 = (absdgx10/(absdgx10 + absdgy10))*gf10;
            Fgy10 = (absdgy10/(absdgx10 + absdgy10))*gf10;
            if(dgx10 > 0)
            {
                Fgx10 *= -1;
            }
            if(dgy10 > 0)
            {
                Fgy10 *= -1;
            }
        }

        // We add all the repulsive forces together
        Fx = (no * (Fx1+Fx2+Fx3+Fx4+Fx5+Fx6+Fx7+Fx8+Fx9+Fx10))+(ng * (Fgx1+Fgx2+Fgx3+Fgx4+Fgx5+Fgx6+Fgx7+Fgx8+Fgx9+Fgx10));
        Fy = (no * (Fy1+Fy2+Fy3+Fy4+Fy5+Fy6+Fy7+Fy8+Fy9+Fy10))+(ng * (Fgy1+Fgy2+Fgy3+Fgy4+Fgy5+Fgy6+Fgy7+Fgy8+Fgy9+Fgy10));

        // We add the repulsive force to the input force
        fx += Fx;
        fy += Fy;
        usleep(100);

        // According to f=ma ==> a=f/m ===(m=1)==> a=f so we can say for each key press we apply a=1 (m/s).
        // we know a=(delta)v so we can say when we press any key the velocity increase 1m/s in that direction.
        vx = fx;
        vy = fy;
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
          
        usleep(10);

        if (vx!=0 || vy!=0) {
            shared_data->computation_in_progress = 1;
        } else {
            shared_data->computation_in_progress = 0;
        }

        // printf("%d    ________    %d   *******   %.2f \n",x1,y1,od1);
        usleep(9000);
    }
    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;
}