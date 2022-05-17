#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("i am children pid: x = %d\n", x);
    } else {
        printf("i am parent pid: x = %d\n", x);
    }
}

void test2() {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("start, i am children pid: x = %d\n", x);
        x = 1000;
        printf("end, i am children pid: x = %d\n", x);
    } else {
        printf("start, i am parent pid: x = %d\n", x);
        x = 10;
        printf("end, i am parent pid: x = %d\n", x);
    }
}

void test3() {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("start, i am children pid: x = %d\n", x);
        x = 1000;
        printf("end, i am children pid: x = %d\n", x);
    } else {
        int wc = wait(NULL);
        printf("start, i am parent pid: x = %d\n", x);
        x = 10;
        printf("end, i am parent pid: x = %d\n", x);
    }
}