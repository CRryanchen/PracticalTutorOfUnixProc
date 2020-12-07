/** smsh1.c small-shell version1
 ** first really useful version after prompting shell
 ** this one parses the command line into strings
 ** use forks, exec, wait, and ignores signals
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "smsh.h"

#define DFL_PROMPT      ">"

int main(void)
{
    char *cmdline, *prompt, **arglist;
    int result;
    void setup();

    prompt = DFL_PROMPT;
    setup();

    while ((cmdline = next_cmd(prompt, stdin)) != NULL)
    {
        if ((arglist = splitline(cmdline)) != NULL)
        {
            result = execute(arglist);
            freelist(arglist);
        }
        free(cmdline);
    }
    
    return 0;
}


void setup(void)
/*
 *
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, car *s2, int n)
{
    fprintf(stderr, "Error: %s, %s\n", s1, s2);
    exit(n);
}