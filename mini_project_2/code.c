#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    foo:
    printf("Process ID: %d\n", getpid());
    printf("The Code address (foo): %p\n", &&foo);
    printf("\nWait... press Enter to exit.\n");
    fgetc(stdin);
    return 0;
}
