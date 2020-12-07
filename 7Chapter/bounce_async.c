/*
 * bounce_async.c
 * purpose      animation with user control, using O_ASYNC on fd
 * note         set_ticker()    sends SIGALRM, handler does animation
 *              kerboard sends SIGIO, main only calls pause()
 * compile      cc bounce_async.c set_ticker.c -lcurses -o bounce_async
 * 
 */

#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

extern void countdown(int signum);
extern int set_ticker(int n_msecs);

/* The state of the game */
#define MESSAGE     "hello"
#define BLANK       "     "

int row = 10;/* current row */
int col = 0;/* current column */
int dir = 1;/* where we are going */
int delay = 200;/* how long to wait */
int done = 0;

int main(void)
{
    void on_alarm(int);/* handler for alarm */
    void on_input(int);/* handler for kerbd */
    void enable_kbd_signals();

    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO, on_input);/* install a handler */
    enable_kbd_signals();/* turn on kbd signals */
    signal(SIGALRM, on_alarm);/* install alarm handler */
    set_ticker(delay);/* start ticking */

    move(row, col);/* get into position */
    addstr(MESSAGE);/* draw initial image */

    while (! done)
    {
        pause();
    }
    
    endwin();

}

void on_input(int signum)
{
    int c = getch();

    if (c == 'Q' || c == EOF)
    {
        done = 1;
    }
    else if (c == ' ')
    {
        dir = -dir;
    }
    
}

void on_alarm(int signum)
{
    signal(SIGALRM, on_alarm);
    mvaddstr(row, col, BLANK);
    col += dir;
    mvaddstr(row, col, MESSAGE);
    refresh();

    /*
     * now handler borders
     */
    if (dir == -1 && col <= 0)
    {
        dir = 1;
    }
    else if (dir == 1 && col + strlen(MESSAGE) >= COLS)
    {
        dir = -1;
    }
}


/*
 * install handler, tell kernel who to notify on input, enable
 * signals
 */
void enable_kbd_signals(void)
{
    int fd_flags;

    fcntl(0, __F_SETOWN, getpid());
    fd_flags = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, (fd_flags | O_ASYNC));
}