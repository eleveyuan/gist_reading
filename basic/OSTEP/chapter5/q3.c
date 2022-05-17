#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // 使用sleep函数，也无法知道子进程是否先于父进程运行完
    int rc = fork();
    if (rc < 0 ) { 
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child: hello\n");
    } else {
        printf("parent: world\n");
    }

    return 0;
}