#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        printf("fork error\n");
        exit(1);
    } else if (rc == 0) {
        int wc = 0; // waitpid(NULL);
        printf("child: %d\n", wc);
    } else {
        int wc = waitpid(rc, NULL, 0);
        printf("parent: %d\n", wc);
    }
    return 0;
}