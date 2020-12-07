/* forkdemo3.c - shows how the return value from fork()
 *               allows a process to determine whether
 *               it is a child or process
 */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fork_rv;

    printf("Before: my pid is %d\n", getpid());

    fork_rv = fork();/* create new process */

    if (fork_rv == -1)
    {
        perror("fork");
    }
    else if (fork_rv == 0)
    {
        printf("I am the child, my pid is %d\n", getpid());
    }
    else
    {
        printf("I am the  parent, my pid is %d\n", getpid());
    }
}