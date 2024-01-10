#include "./../include/goal.h"

int main()
{
    // Initialize Shared Memory
    int shm_fd = shm_open("/my_shared_memory", O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    shared_data->reachedAllTheGoals = 1;

    while (TRUE)
    {
        while(shared_data->reachedAllTheGoals)
        {
            importObstacleCoordinates();
            spawn_random_g();
            shared_data->reachedAllTheGoals = 0;
            usleep(1000);
        }
    }
    // spawn_random_o();

    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;
}