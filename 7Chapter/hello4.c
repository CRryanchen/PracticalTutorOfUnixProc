/* hello4.c
 * purpose show how to use erase, and draw for animation
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>

int main(void)
{
    int i;

    initscr();
    clear();
    for (i = 0; i < LINES; i++)
    {
        move(i, i++);
        if (i % 2 == 1)
        {
            standout();
        }
        addstr("Hello, World");
        if (i % 2 == 1)
        {
            standend();
        }
        refresh();
        sleep(1);
        move(i, i-1);/* move back */
        addstr("             ");/* rease line */
    }
    endwin();
}