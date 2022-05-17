#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        printf("fork error\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("child\n");
    } else {
        int wc = wait(NULL);
        printf("%d\n", wc);
    }
    return 0;
}