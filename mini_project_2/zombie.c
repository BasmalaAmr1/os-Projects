#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pid = fork();
    if (pid == 0) {
        printf("Child: I am dying now... I will become a zombie.\n");
        exit(0); 
    } else {
        printf("Parent: I am sleeping for 60 seconds. PID: %d\n", getpid());
        printf("Check 'ps -l' now to see the zombie child!\n");
        sleep(60);
        printf("Parent: Finished.\n");
    }
    return 0;
}
