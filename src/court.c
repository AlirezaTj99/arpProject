#include "./../include/court.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <ncurses.h>

#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char const *argv[]){

    // Initialize Shared Memory for the Blackboard
        int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("shm_open");
            exit(EXIT_FAILURE);
        }
        ftruncate(shm_fd, sizeof(SHARED_DATA));
        shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // void initialize_court(int width, int height) {
    //     // Initialize the properties of the court
    //     court.startx = 0;  // Example starting position, adjust as needed
    //     court.starty = 0;  // Example starting position, adjust as needed
    //     court.width = width;
    //     court.height = height;

    //     // Additional initialization code can go here
    // }

    // void update_court() {
    //     // Implementation to update the court's properties or state
    //     // This function can be used to change the dimensions or other properties of the court dynamically

    //     // Example: Increase the size of the court
    //     court.width += 1;
    //     court.height += 1;

    //     // Add any additional logic to update the state of the court as needed
    // }

    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;

}