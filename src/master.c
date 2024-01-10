#include "./../include/master.h"

int main() {
    // Set up signal handling
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Initialize Shared Memory
    int shm_fd = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(shm_fd, sizeof(SHARED_DATA));
    shared_data = mmap(NULL, sizeof(SHARED_DATA), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    usleep(1000);

    // Initialize User Interface
    init_console_ui();
    usleep(100);

    // Spawn input Process
    char *arg_list_input[] = {"/usr/bin/konsole", "-e", "./bin/input", NULL};
    pid_t pid_input = spawn("/usr/bin/konsole", arg_list_input);

    // Spawn force Process
    char *arg_list_force[] = {"/usr/bin/konsole", "-e", "./bin/force", NULL};
    pid_t pid_force = spawn("/usr/bin/konsole", arg_list_force);

    // Spawn obstacle Process
    char *arg_list_obstacle[] = {"/usr/bin/konsole", "-e", "./bin/obstacle", NULL};
    pid_t pid_obstacle = spawn("/usr/bin/konsole", arg_list_obstacle);

    // Spawn goal Process
    char *arg_list_goal[] = {"/usr/bin/konsole", "-e", "./bin/goal", NULL};
    pid_t pid_goal = spawn("/usr/bin/konsole", arg_list_goal);

    // Spawn Watchdog Process
    char *arg_list_watchdog[] = {"/usr/bin/konsole", "-e", "./bin/watchdog", NULL};
    pid_t pid_watchdog = spawn("/usr/bin/konsole", arg_list_watchdog);

    // Infinite Loop
    while (1) {
        // Get mouse/resize commands in non-blocking mode...
        int cmd = getch();

        if (shared_data->close_master) {
            // Perform cleanup
            cleanup();

            // Exit the program
            exit(0);
        }

        // Update UI
        update_console_ui(&shared_data->ee_x, &shared_data->ee_y, &shared_data->vx, &shared_data->vy, blackboard);
    }

    // Cleanup
    cleanup();

    // Wait for the processes to finish
    int status_input, status_force, status_obstacle, status_goal, status_watchdog;
    waitpid(pid_goal, &status_goal, 0);
    waitpid(pid_input, &status_input, 0);
    waitpid(pid_force, &status_force, 0);
    waitpid(pid_obstacle, &status_obstacle, 0);
    waitpid(pid_watchdog, &status_watchdog, 0);

    return 0;
}