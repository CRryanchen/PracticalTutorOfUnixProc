/* prompting shell version 1
 * Prompts for the command and its arguments
 * Builds the argument vector for the call to execvp
 * Uses execvp(), and never returns
 */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int execute(char *arglist[]);
char *makestring(char *buf);


#define MAXARGS     20/* cmdline args */
#define ARGLEN     100/* token length */

int main(void)
{
    char *arglist[MAXARGS + 1];/* an array of ptrs */
    int numargs;/* index into array */
    char argbuf[ARGLEN];/* read stuff here */
    char *makestring();/* malloc etc */

    numargs = 0;
    while (numargs < MAXARGS)
    {
        printf("Arg[%d]?", numargs);
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
        {
            arglist[numargs++] = makestring(argbuf);
        }
        else
        {
            if (numargs > 0)
            {
                arglist[numargs] = NULL;
                execute(arglist);
                numargs = 0;
            }
            
        }
    }

    return 0;

}

int execute(char *arglist[])
{
    execvp(arglist[0], arglist);
    perror("execvp failed");
    exit(1);
}

char *makestring(char *buf)
{
    char *cp;

    buf[strlen(buf) - 1] = '\0';
    cp = malloc(strlen(buf) + 1);
    if (cp == NULL)
    {
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}