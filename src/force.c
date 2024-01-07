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

    while(TRUE)
    {
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
        // According to f=ma ==> a=f/m ===(m=1)==> a=f so we can say for each key press we apply a=1 (m/s).
        // we know a=(delta)v so we can say when we press any key the velocity increase 1m/s in that direction.
        vx = fx;
        vy = fy;

        ee_x += (vx/100);
        ee_y += (vy/100);
        shared_data->x = ee_x;
        shared_data->y = ee_y;
        shared_data->Vx = vx;
        shared_data->Vy = vy;

        if (vx!=0 || vy!=0) {
            shared_data->computation_in_progress = 1;
        } else {
            shared_data->computation_in_progress = 0;
        }

        printf("%.2f    ________    %.2f \n",ee_x,ee_y);
        usleep(9000);
    }
    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;
}