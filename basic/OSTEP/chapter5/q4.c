#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    int rc = fork();
    char *cmd = "/bin/ls";
    char *arg[] = {"ls", "-a", NULL};

    if (rc < 0) {
        printf("fork error\n");
        exit(1);
    } else if (rc == 0) {
        //    exec不会返回,所以第一条execl语句后的语句不会被执行
        // execl(cmd, "ls", NULL);
        execlp(cmd, "ls", NULL);
        // execve(cmd, arg, envp);
        // execv(cmd, arg);
        // execvp(cmd, arg);
        // execle(cmd, "ls", NULL, envp);
    } else {
        int wc = wait(NULL);
    }
    return 0;
}