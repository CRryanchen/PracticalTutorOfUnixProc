/* hello.c
 * purpose: show how to use curses functions with a loop
 * outline initialize, draw stuff, wrap up
 */

#include <stdio.h>
#include <curses.h>

int main(void)
{
    int i;

    initscr();/* tuan on curses */
    clear();/* clear screen */
    for ( i = 0; i < LINES; i++)
    {
        move(i, i + 1);
        if (i % 2 == 1)
        {
            standout();
        }
        addstr("Hello, World");
        if (i % 2 == 1)
        {
            standend();
        }
    }
    refresh();/* update the screen */
    getch();/* wait for use input */

    endwin();/* turn off scrses */

    return 0;
}