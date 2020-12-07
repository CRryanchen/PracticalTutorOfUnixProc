/* sigactdemo.c
 *              purpose: shows use of sigaction()
 *              feature: blocks ^\ while handling ^C
 *                       doesn't not reset ^C handler, so two kill
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define INPUTLEN        100

int main(void)
{
    struct sigaction newhandler;/* new settings */
    sigset_t blocked;/* set of blocked sigs */
    void inthandler();/* the handler */
    char x[INPUTLEN];

    /* load these two members first */
    newhandler
}