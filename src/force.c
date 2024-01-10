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
        int R = 10;                  // Radios of efficeint repulsive force
        float n = 10.0;               // the reoulsive force gain

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
        if(od1 < R)
        {
            float of1=0.0;            
            float absdx1 = fabs (dx1);
            float absdy1 = fabs (dy1);
            
            of1 = 0.5 * pow(((1.0 / od1) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od2 < R)
        {
            float of2=0.0;            
            float absdx2 = fabs (dx2);
            float absdy2 = fabs (dy2);
            
            of2 = 0.5 * pow(((1.0 / od2) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od3 < R)
        {
            float of3=0.0;            
            float absdx3 = fabs (dx3);
            float absdy3 = fabs (dy3);
            
            of3 = 0.5 * pow(((1.0 / od3) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od4 < R)
        {
            float of4=0.0;            
            float absdx4 = fabs (dx4);
            float absdy4 = fabs (dy4);
            
            of4 = 0.5 * pow(((1.0 / od4) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od5 < R)
        {
            float of5=0.0;            
            float absdx5 = fabs (dx5);
            float absdy5 = fabs (dy5);
            
            of5 = 0.5 * pow(((1.0 / od5) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od6 < R)
        {
            float of6=0.0;            
            float absdx6 = fabs (dx6);
            float absdy6 = fabs (dy6);
            
            of6 = 0.5 * pow(((1.0 / od6) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od7 < R)
        {
            float of7=0.0;            
            float absdx7 = fabs (dx7);
            float absdy7 = fabs (dy7);
            
            of7 = 0.5 * pow(((1.0 / od7) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od8 < R)
        {
            float of8=0.0;            
            float absdx8 = fabs (dx8);
            float absdy8 = fabs (dy8);
            
            of8 = 0.5 * pow(((1.0 / od8) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od9 < R)
        {
            float of9=0.0;            
            float absdx9 = fabs (dx9);
            float absdy9 = fabs (dy9);
            
            of9 = 0.5 * pow(((1.0 / od9) - (1.0 / R)), 2);
            usleep(1000);
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
        if(od10 < R)
        {
            float of10=0.0;            
            float absdx10 = fabs (dx10);
            float absdy10 = fabs (dy10);
            
            of10 = 0.5 * pow(((1.0 / od10) - (1.0 / R)), 2);
            usleep(1000);
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

        // We add all the repulsive forces together
        Fx = n * (Fx1+Fx2+Fx3+Fx4+Fx5+Fx6+Fx7+Fx8+Fx9+Fx10);
        Fy = n * (Fy1+Fy2+Fy3+Fy4+Fy5+Fy6+Fy7+Fy8+Fy9+Fy10);

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