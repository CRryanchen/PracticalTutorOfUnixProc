/* whotofile.c
 * purpose: show how to redirect output for another program
 *   idea: fork, then in the child, redirect output, then exec
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
    int pid;
    int fd;

    printf("About to run who into a file\n");

    /* create a new process or quit */
    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }
    
    /* child does the work */
    if (pid == 0)
    {
        close(1);
        fd = creat("userlist", 0644);
        execlp("who", "who", NULL);
        perror("execlp");
        exit(1);
    }
    
    /* parent waits then reports */
    if (pid != 0)
    {
        wait(NULL);
        printf("Done running who. results in userlist\n");
    }
    
    return 0;
}