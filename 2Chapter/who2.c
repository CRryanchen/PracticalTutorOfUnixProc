/* who2.c -- read /etc/utmp and list info therein
 *        -- suppresses empty records
 *        -- formats time nicely
 */

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>/* use ecit() */
#include <time.h>

void showtime(long);
void show_info(struct utmp *utbufp);

// #define SHOWHOST               /* include remote machine on output */

int main(void)
{
    struct utmp utbuf;     /* read info into here */
    int utmpfd;                     /* read from this descriptor */

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);          /* UTMP_FILE is in utmp.h */
        exit(1);
    }

    while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
    {
        show_info(&utbuf);
    }

    close(utmpfd);

    return 0;                       /* went ok */
}


/*
 * show_info()
 *              displays contents of the utmp struct 
 *              in human readable form
 *              * displays nothing if record has no user name
 */
void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
    {
        return;
    }
    
    printf("%-8.8s", utbufp->ut_name);          /* the logname */
    printf(" ");                                /* a space */
    printf("%-8.8s", utbufp->ut_line);          /* the tty */
    printf(" ");                                /* a space */
    showtime(utbufp->ut_time);                  /* login time */
    printf(" ");
#ifdef SHOWHOST
    if (utbufp->ut_host[0] != '\0')
    {
        printf("(%s)", utbufp->ut_host);        /* the host */
    }
#endif
    printf("\n");                               /* newline */

}

void showtime(long timeval)
{
    /*
     * display time in a formal fit for human consumption
     * uses ctime to build a string then picks parts out of it
     * Note: %12.12s printfs a strubf 12chars with and LIMITS
     * it to 12chars.
     */
    char * cp;                 /* to hold address of time */
    cp = ctime(&timeval);      /* convert time to string */
                               /* string looks like */
                               /* Mon Feb 4 00:46:40 EST 1991 */
                               /* 0123456789012345. */
    printf("%12.12s", cp + 4); /* pick 12 chars from pos 4 */
}