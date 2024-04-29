/*
 * CYANCORE LICENSE
 * Copyrights (C) 2019, Cyancore Team
 *
 * File Name		: scanf.c
 * Description		: This file contains sources of libc-scanf
 *			  inspired from gnu-libc
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#include <stddef.h>
#include <stdint.h>
#include <status.h>
#include <ccpfs.h>
#include <stdio.h>
#include <stddev.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

int fgetc(const FILE *dev, char *c)
{
	return ccpdfs_read(dev, c);
}

char getch()
{
    char c;
    fgetc(stdin, &c);
    return c;
}

char getchar()
{
    char c = '0', temp;
    do
    {
        temp = getch();
        fputc(stdout, temp);
        if(temp == '\r')
        	fputc(stdout, '\n');
	else
		c = temp;
    } while(temp != '\r');
    return c;
}

/**
 * get string with spaces
 *
 * @brief This function will take string input with spaces
 *
 */
char *gets()
{
	char *s = (char *)malloc(sizeof(char)), temp;
	int i = 0;
	do
	{
		temp = getch();
		fputc(stdout, temp);
		if(temp == '\r')
		{
			fputc(stdout, '\n');
		}
		else
		{
			s[i++] = temp;
		}
	} while(temp != '\r');
	return s;
}

/**
 * scanf
 *
 * @brief This function will take standard input for default data types.
 *	  input will break at spaces
 *
 */

#define CURRCHAR (temp)
#define CHARIN() (temp = getch())
int scanf(const char * restrict fmt, ...)
{
	unsigned int count = 0;
	char c = '0', temp;
	va_list ap;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			/* char length : %7d */
			unsigned int cl = 0;
			while (isDigit(*fmt))
			{
				cl *= 10;
				cl += *fmt++ - '0';
			}
			switch (*fmt++)
			{
				case 'c':
				{
					/* skip leading spaces */
					while (isSpace(CHARIN()))
					{
						if (CURRCHAR == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, CURRCHAR);
					}
					fputc(stdout, CURRCHAR);
					c = CURRCHAR;
					while (CHARIN())
					{
						fputc(stdout, CURRCHAR);
						if (isSpace(CURRCHAR))
							break;
					}
					fputc(stdout, '\n');
					*(char *)va_arg(ap, char *) = c;
					count++;
					break;
				}
				case 's':
				{
					char *s = va_arg(ap, char *);
					/* skip leading spaces */
					while (isSpace(CHARIN()))
					{
						if (CURRCHAR == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, CURRCHAR);
					}
					fputc(stdout, CURRCHAR);
					*s++ = CURRCHAR;
					while (CHARIN())
					{
						fputc(stdout, CURRCHAR);
						if (isSpace(CURRCHAR))
							break;
						*s++ = CURRCHAR;
					}
					fputc(stdout, '\n');
					*s = '\0';
					count++;
					break;
				}
				case 'u':
				case 'd':
				{
					int a = 0;
					/* skip leading spaces */
					while (isSpace(CHARIN()))
					{
						if (CURRCHAR == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, CURRCHAR);
					}
					fputc(stdout, CURRCHAR);
					c = CURRCHAR;
					while (CHARIN())
					{
						a *= 10;
						if (isDigit(c))
							a += (c - '0');
						else
							a += (int)c;
						if (isSpace(CURRCHAR))
							break;
						c = CURRCHAR;
						fputc(stdout, CURRCHAR);
					}
					fputc(stdout, '\n');
					*(int *)va_arg(ap, int *) = a;
					count++;
					break;
				}
				case 'f':
				{
					char *a = gets();
					*(float *)va_arg(ap, float *) = (float)atof(a);
					count++;
					break;
				}
				default:
					break;
			}
			continue;
		}
		/* increment pointer if % not found */
		fmt++;
	}
	return count;
}
