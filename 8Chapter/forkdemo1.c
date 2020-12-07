
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(void)
{
    int ret_drom_fork, mypid;

    mypid = getpid();
    printf("Before: my pid is %d\n", mypid);

    ret_drom_fork = fork();

    sleep(1);
    printf("After: my pid is %d, fork() said %d\n", getpid(), ret_drom_fork);
}