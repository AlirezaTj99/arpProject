#include "./../include/watchdog.h"

int main() {

    int fd1; 
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
    char str1[80]; 
    char format_string[80]="%d";
    int masterTerminate = 1;

    int fd13; 
    char * myfifo13 = "/tmp/myfifo13"; 
    mkfifo(myfifo13, 0666); 
    char str13[80]; 
    char format_string13[80]="%d";

    while (1) {

        fd13 = open(myfifo13,O_RDONLY);
        if (fd13 == -1) {
            perror("Error opening FIFO13");
        }
        read(fd13, str13, 80);
        sscanf(str13, format_string13, &computation_in_progress);
        close(fd13);
        sleep(1);  
        printf(".....%d\n",computation_in_progress);
        
        // Check if computation is in progress
        if (computation_in_progress) {

            no_computation_count = 1;
            printf("computation_in_progress output = %d ===>>> Watchdog: Good condition...\n",computation_in_progress);

        }
        else {
            printf("computation_in_progress output = %d, no_computation_count = %d ===>>> Watchdog: No computation in progress. Sending notification...\n",computation_in_progress,no_computation_count);

            no_computation_count++;
        }

        if (no_computation_count > 25) {
            // No computation is ongoing for the specified timeout duration; take action
            printf("No computation is ongoing for %d seconds! Stopping the system...\n",no_computation_count);
            sleep(10);
            fd1 = open(myfifo,O_WRONLY); 
            if (fd1 == -1) {
                perror("Error opening FIFO1");
            }
            sprintf(str1, format_string, masterTerminate);     // Signal to master to close
            write(fd1, str1, strlen(str1)+1); 
            close(fd1);
            exit(EXIT_FAILURE);
        }
        computation_in_progress = 0;
    }

    // Cleanup
    endwin();

    return 0;
}

// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483