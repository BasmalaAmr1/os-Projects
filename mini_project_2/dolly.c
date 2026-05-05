#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // هذا الجزء ينفذه الابن (Child)
        printf("Hello! I am the CHILD. My PID is %d, and my Parent is %d\n", getpid(), getppid());
    } else {
        // هذا الجزء ينفذه الأب (Parent)
        printf("Hi! I am the PARENT. My PID is %d, and my Child is %d\n", getpid(), pid);
    }

    return 0;
}
