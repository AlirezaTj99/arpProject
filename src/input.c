#include "./../include/input.h"

int main(int argc, char const *argv[])
{
    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;

    // End-effector coordinates
    float ee_x, ee_y;

    // Defining the velocities
    float vx = 0;
    float vy = 0;

    // Initialize Shared Memory
    int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize User Interface 
    init_console_ui();

    // Infinite loop
    while(TRUE)
    {  
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();

        // If user resizes screen, re-draw UI
        if(cmd == KEY_RESIZE) {
            if(first_resize) {
                first_resize = FALSE;
            }
            else {
                reset_console_ui();
            }
        }

        // if (vx!=0 || vy!=0) {
        //     shared_data->computation_in_progress = 1;
        // } else {
        //     shared_data->computation_in_progress = 0;
        // }
        
        // The key commands ...
        switch (cmd)
        {
            // for each key press we apply a 1N force for 1 second, and send the signal to shared data.
            case '7':
                shared_data->xForceDecrease = 1;
                shared_data->yForceDecrease = 1;
                // vx--;
                // vy--;
                break;
            case '9':
                shared_data->xForceIncrease = 1;
                shared_data->yForceDecrease = 1;
                // vx++;
                // vy--;
                break;
            case '1':
                shared_data->yForceIncrease = 1;
                shared_data->xForceDecrease = 1;
                // vx--;
                // vy++;
                break;
            case '3':
                shared_data->xForceIncrease = 1;
                shared_data->yForceIncrease = 1;
                // vx++;
                // vy++;
                break;
            case '4':
                shared_data->xForceDecrease = 1;
                // vx--;
                break;
            case '6':
                shared_data->xForceIncrease = 1;
                // vx++;
                break;
            case '8':
                shared_data->yForceDecrease = 1;
                // vy--;
                break;
            case '2':
                shared_data->yForceIncrease = 1;
                // vy++;
                break;
            case '5':
                shared_data->zeroForce = 1;
                // vy = 0;
                // vx = 0;
                break;
            case 'q':
                shared_data->close_master = 1;  // Signal to master to close
                endwin();                       // End curses mode
                exit(0);                        // Exit the program
                break;
            default:
                break;
        }
        // we know that v=(delta)x so we can say in each second we have: ee_x' = ee_x + vx and the same for vy
        // ee_x += (vx/100);
        // ee_y += (vy/100);
        
        // Read the values of the floats
        ee_x = shared_data->x;
        ee_y = shared_data->y;
        vx = shared_data->Vx;
        vy = shared_data->Vy;
        usleep(10000);
            
        // Update UI
        update_console_ui(&ee_x, &ee_y, &vx, &vy, blackboard);
    }

    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;
}