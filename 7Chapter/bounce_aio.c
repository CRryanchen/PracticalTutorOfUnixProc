/*
 * bounce_aio.c
 * purpose      animation with user control, using aio_read () etc
 * note         set_ticker()    sends SIGALRM, handler does animation
 *              kerboard sends SIGIO, main only calls pause()
 * compile      cc bounce_async.c set_ticker.c -lcurses -lrt -o bounce_async
 * 
 */

#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <aio.h>

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

struct aiocb kbcbuf;/* an aio control buf */

int main(void)
{
    void on_alarm(int);/* handler for alarm */
    void on_input(int);/* handler for kerbd */
    void setup_aio_buffer();

    initscr();
    crmode();
    noecho();
    clear();

    signal(SIGIO, on_input);/* install a handler */
    setup_aio_buffer();/* initialize aio ctrl buff */
    aio_read(&kbcbuf);/* place a read request */

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
    int c;
    char *cp = (char *)kbcbuf.aio_buf;

    if (aio_error(&kbcbuf) !=0)
    {
        perror("reading failed");
    }
    else
    {
        if (aio_return(&kbcbuf) == 1)
        {
            c = *cp;
            if (c == 'Q' || c == EOF)
            {
                done = 1;
            }
            else if (c == ' ')
            {
                dir = -dir;
            }
        }
    }

    aio_read(&kbcbuf);
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



void setup_aio_buffer(void)
{
    static char input[1];

    kbcbuf.aio_fildes = 0;
    kbcbuf.aio_buf = input;
    kbcbuf.aio_nbytes = 1;
    kbcbuf.aio_offset = 0;

    kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    kbcbuf.aio_sigevent.sigev_signo = SIGIO;
}