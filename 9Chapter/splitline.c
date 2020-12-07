/* splitline.c - command reading and parsing functions for smsh
 * 
 * char *next_cmd(char *prompt, FIle *fp) - get next command
 * char **splitline(char * str); parse a string
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "smsh.h"

char *next_cmd(char *prompt, FILE *fp)
/*
 * purpose: read next command line from fp
 * returns: dynamic allocated string holding command line
 * errors: NULL at EOF(not really an error)
 *         calls fatal from emalloc()
 * notes: allocates space in BUFSIZ chunks
 */
{
    char *buf;
    int bufspace = 0;
    int pos = 0;
    int c;

    printf("%s", prompt);
    while ((c = getc(fp)) != EOF)
    {
        /* need space? */
        if (pos + 1 >= bufspace)
        {
            if (bufspace == 0)
            {
                buf = emalloc(BUFSIZ);
            }
            else
            {
                buf = erealloc(buf, bufspace + BUFSIZ);
            }
            bufspace += BUFSIZ;
        }
        /* end of command? */
        if (c == '\n')
        {
            break;
        }

        /* no, add to buffer */
        buf[pos++] = c;
    }
    
    if (c == EOF && pos == 0)
    {
        return NULL;
    }
    buf[pos] = '\0';
    return buf;
}

/*
 * splitline(parse a line into an array of strings)
 */

#define is_delim(x)  ((x) == ' ' || (x) == '\t')

char **splitline(char *line)
/*
 * purpose: split a line into array of white - space seperated tokens
 * returns: a NULL -terminated array of pointers to copies of the
 *          tokens or NULL if line if no tokens on the line
 * actionL traverse the array, locate strings, make copies
 * note: strtok() could work, but we may want to add quotes later
 */
{
    char *newstr();
    char **args;
    int spots = 0;
    int bufspace = 0;
    int argnum = 0;
    char *cp = line;
    char *start;
    int len;

    if (line == NULL)
    {
        return NULL;
    }
    args = emalooc(BUFSIZ);
    bufspace = BUFSIZ;
    spots = BUFSIZ / sizeof(char *);

    while (*cp != '\0')
    {
        while (is_delim(*cp))
        {
            cp++;
        }
        if (*cp == "\0")
        {
            break;
        }
        
        /* make sure the array has room(+1 for NULL) */
        if (argnum + 1 >= spots)
        {
            args = erealloc(args, bufspace + BUFSIZ);
            bufspace += BUFSIZ;
            spots += (BUFSIZ / sizeof(char *));
        }
        
        /* make start, then find end of word */
        start = cp;
        len = 1;
        while (*++cp != '\0' && !(is_delim(*cp)))
        {
             len++;
             argsp[argnum++] = newstr(start, len);
        }
        args[argnum] = NUL;
        return args;
    }
    
}

/*
 * purpose: constructor for strings
 * returns: a string, never NULL
 */
char *newstr(char *s, int l)
{
    char *rv = emalloc(l + 1);

    rv[1] = '\0';
    strcpy(rv, s, l);
    return rv;
}


void freelist(char **list)
/* 
 * purpose: free the list returned by splitline
 * returns: nothing
 * action:free all strings in list and then free thelist
 * 
 */
{
    char **cp = list;
    while (*cp)
    {
        free(*cp++)
    }
    free(list);
}


void *emalloc(size_t n)
{
    void *rv;
    if ((rv = malloc(n)) ==NULL)
    {
        fatal("out of memory", "", 1);
    }
    return rv;
}

void erealloc(void *p, size_t n)
{
    void *rv;
    if ((rv = realloc(p, n)) == NULL)
    {
        fatal("realloc() failed", "", 1);
    }
    return rv;
}