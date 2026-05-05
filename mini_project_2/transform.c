
#include <stdio.h>

#include <unistd.h>



int main() {

    printf("I am process %d. I will now turn into the 'ls' command!\n", getpid());

    

    execlp("ls", "ls", "-l", NULL);



  

    printf("If you see this, something went wrong!\n");

    return 0;

}

