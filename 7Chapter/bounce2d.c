/* bounce2d 1.0
 * bounce a character(default is 'o')around the screen
 * defined by some parameters
 * 
 * user input: s slow down x component,S slow y conponent
 *             f speed x component, F: speen y component
 *              Q quit
 * blocks on read, but timer tick sends SIGALRM caught by call_move
 * build:  cc bounce2d.c set_ticker.c -l curses -o bounce2d
 */

#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>

#include "bounce.h"

struct ppball the_ball;

/* the main loop */

extern void countdown(int signum);
extern int set_ticker(int n_msecs);


void set_up(void);
void wrap_up(void);
void ball_move(int signum);
int bounce_or_lose(struct ppball *bp);


/* some global settings main and the handler use */



int main(void)
{
    int c;/* user input */

    set_up();
    

    while ((c = getchar()) != 'Q')
    {
        
        if (c == 'f')
        {
            the_ball.x_ttm--;
        }
        else if (c == 's')
        {
            the_ball.x_ttm++;
        }
        else if (c == 'F')
        {
            the_ball.y_ttm--;
        }
        else if (c == 'S')
        {
            the_ball.y_ttm++;
        }
        
    }

    wrap_up();
}

void set_up(void)
/*
 * init structure and other stuff
 */
{
    void ball_move(int);

    the_ball.y_pos = Y_INIT;
    the_ball.x_pos = X_INIT;
    the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
    the_ball.x_ttg = the_ball.x_ttm = X_TTM;
    the_ball.y_dir = 1;
    the_ball.x_dir = 1;
    the_ball.symbol = DFL_SYMBOL;

    initscr();
    noecho();
    crmode();

    signal(SIGINT, SIG_IGN);
    mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
    refresh();

    signal(SIGALRM, ball_move);
    set_ticker(1000 / TICKS_PER_SEC);
}


void wrap_up(void)
{
    set_ticker(0);
    endwin();
}



void ball_move(int signum)
{
    int y_cur, x_cur, moved;

    signal(SIGALRM, SIG_IGN);
    y_cur = the_ball.y_pos;
    x_cur = the_ball.x_pos;
    moved = 0;

    if (the_ball.y_ttm > 0 && the_ball.y_ttg-- == 1)
    {
        the_ball.y_pos += the_ball.y_dir;
        the_ball.y_ttg = the_ball.y_ttm;
        moved = 1;
    }
    
    if (the_ball.x_ttm > 0 && the_ball.x_ttg-- == 1)
    {
        the_ball.x_pos += the_ball.x_dir;
        the_ball.x_ttg = the_ball.x_ttm;
        moved = 1;
    }
    
    if (moved)
    {
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(y_cur, x_cur, BLANK);
        mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol);
        bounce_or_lose(&the_ball);
        move(LINES - 1, COLS - 1);
        refresh();
    }
    signal(SIGALRM, ball_move);
}

int bounce_or_lose(struct ppball *bp)
{
    int return_val = 0;

    if (bp->y_pos == TOP_ROW)
    {
        bp->y_dir = 1;
        return_val = 1;
    }
    else if (bp->y_pos == BOT_ROW)
    {
        bp->y_dir = -1;
        return_val = 1;
    }
    if (bp->x_pos == LEFT_EDGE)
    {
        bp->x_dir = 1;
        return_val = 1;
    }
    else if (bp->x_pos == RIGHT_EDGE)
    {
        bp->x_dir = -1;
        return_val = 1;
    }
    
    return return_val;
}