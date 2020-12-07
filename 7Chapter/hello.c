/* hello.c
 * purpose: show the minial calls needed to use curses
 * initialize, draw stuff, wait for input ,quit
 */

#include <stdio.h>
#include <curses.h>

int main(void)
{
    initscr();/* tuan on curses */

    clear();/* clear screen */
    move(10, 20);/* row10, col20 */
    addstr("Hello,World");/* add a string */
    refresh();/* update the screen */
    getch();/* wait for use input */

    endwin();/* turn off scrses */

    return 0;
}