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

    // shared_data->allowGoalSpawn = 1;

    while (TRUE)
    {
        while(shared_data->allowGoalSpawn)
        {
            shared_data->reachedGoal1 = 0;
            shared_data->reachedGoal2 = 0;
            shared_data->reachedGoal3 = 0;
            shared_data->reachedGoal4 = 0;
            shared_data->reachedGoal5 = 0;
            shared_data->reachedGoal6 = 0;
            shared_data->reachedGoal7 = 0;
            shared_data->reachedGoal8 = 0;
            shared_data->reachedGoal9 = 0;
            shared_data->reachedGoal10 = 0;
            importObstacleCoordinates();
            spawn_random_g();
            shared_data->allowGoalSpawn = 0;
            usleep(1000);
        }
    }

    // Cleanup
    endwin();
    munmap(blackboard, sizeof(BLACKBOARD_DATA));
    shm_unlink("/my_shared_memory");

    return 0;
}