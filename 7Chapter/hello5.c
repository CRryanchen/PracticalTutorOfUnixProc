/* hello4.c
 * purpose bounce a message back and forth across the screen
 * commpile cc hello5.c -lcurse -o hello5
 */

#include <stdio.h>
#include <curses.h>
#include <unistd.h>

#define LEFTEDGE    10
#define RIGHTEDGE   30
#define ROW         10

int main(void)
{
    char *message = "Hello";
    char *blank =   "     ";
    int dir = +1;
    int pos = LEFTEDGE;

    initscr();
    clear();

    while (1)
    {
        move(ROW, pos);
        addstr(message);/* draw string */
        move(LINES - 1, COLS - 1);/* parking the cursor */
        refresh();/* show string */
        sleep(1);
        move(ROW, pos);/* erase string */
        addstr(blank);
        pos += dir;/* advance string */
        if (pos >= RIGHTEDGE)/* check for bonuce */
        {
            dir = -1;
        }
        if (pos <= LEFTEDGE)
        {
            dir = +1;
        }
    }

    endwin();
}