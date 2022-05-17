#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>  // open()函数原型

void test1();
void test2();
void test3();

int main(int argc, char *argv[]) {
    int flag = 0;
    if (argc !=2 || (flag = atoi(argv[1])) > 3 || (flag = atoi(argv[1])) < 1) {
        printf("Usage: %s 1, 2 or 3\n", argv[0]);
        return 0;
    }
    switch (flag)
    {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    default:
        break;
    }

    return 0;
}

void test1() {
    int fw = open("./test.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *buf = "child\n";
        int error = write(fw, buf, sizeof(char) * strlen(buf));
        printf("child error: %d\n", error == -1 ? 1 : 0);
    } else {
        int wc = wait(NULL);
        char *buf = "parent\n";
        int error = write(fw, buf, sizeof(char) * strlen(buf));
        printf("parent error: %d\n", error == -1 ? 1 : 0);
    }
    close(fw);
}

void test2() {
    int fw = open("./test.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *buf = "child\n";
        int error = write(fw, buf, sizeof(char) * strlen(buf));
        printf("child error: %d\n", error == -1 ? 1 : 0);
    } else {
        char *buf = "parent\n";
        int error = write(fw, buf, sizeof(char) * strlen(buf));
        printf("parent error: %d\n", error == -1 ? 1 : 0);
    }
}

void test3() {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        
    } else {
        int wc = wait(NULL);

    }
}