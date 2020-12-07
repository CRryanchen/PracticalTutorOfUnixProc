/* execute.c - code used by shamm shell to execute commands */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 * erroes: -1 on fork() or wait() errors
 */
{
    int pid;
    int child_info = -1;

    if (argv[0] == NULL)
    {
        return 0;
    }
    
    if ((pid = fork()) == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        execvp(argv[0], argv);
        perror("cannot execute command");
        exit(1);
    }
    else
    {
        if (wait(&child_info) == -1)
        {
            perror("Wait");
        }
    }

    return child_info;
}