#include "./../include/inspection_utilities.h"

SHARED_DATA *shared_data;

int main(int argc, char const *argv[])
{
    // Utility variable to avoid trigger resize event on launch
    int first_resize = TRUE;

    // End-effector coordinates
    float ee_x, ee_y;

    // Defining the velocities
    int vx = 0;
    int vy = 0;

    // Initialize Shared Memory for the Blackboard
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
        
        // The key commands ...
        switch (cmd)
        {
            // for each key press we apply a 1N force for 1 second, according to f=ma ==> a=f/m ===(m=1)==> a=f so we can say for each key press we apply a=1m/s.
            // we know a=(delta)v so we can say when we press any key the velocity increase 1m/s in that direction.
            case '7':
                vx--;
                vy--;
                break;
            case '9':
                vx++;
                vy--;
                break;
            case '1':
                vx--;
                vy++;
                break;
            case '3':
                vx++;
                vy++;
                break;
            case '4':
                vx--;
                break;
            case '6':
                vx++;
                break;
            case '8':
                vy--;
                break;
            case '2':
                vy++;
                break;
            default:
                break;
        }
        // we know that v=(delta)x so we can say in each second we have: ee_x' = ee_x + vx and the same for vy
        ee_x += vx;
        ee_y += vy;
        sleep(1);
        
        // Update UI
        update_console_ui(&ee_x, &ee_y, &vx, &vy, blackboard);
  }

    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;
}