/* forkdemo2.c - show how child processes pick up at the return
 *               form fork() and can execute any code they like
 *               even fork. Predict number of lines of output
 */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("my pid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("my pid is %d\n", getpid());
}