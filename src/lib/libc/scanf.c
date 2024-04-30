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
char *gets(char *str)
{
	char *p = str;
	char temp;
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
			*str++ = temp;
		}
	} while(temp != '\r');
	str = '\0';
	return p;
}

/**
 * scanf
 *
 * @brief This function will take standard input for default data types.
 *	  input will break at spaces
 *
 */

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
					while (isSpace(temp = getch()))
					{
						if (temp == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, temp);
					}
					fputc(stdout, temp);
					c = temp;
					while ((temp = getch()))
					{
						fputc(stdout, temp);
						if (isSpace(temp))
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
					while (isSpace(temp = getch()))
					{
						if (temp == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, temp);
					}
					fputc(stdout, temp);
					*s++ = temp;
					while ((temp = getch()))
					{
						fputc(stdout, temp);
						if (isSpace(temp))
							break;
						*s++ = temp;
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
					while (isSpace(temp = getch()))
					{
						if (temp == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, temp);
					}
					fputc(stdout, temp);
					c = temp;
					while ((temp = getch()))
					{
						a *= 10;
						if (isDigit(c))
							a += (c - '0');
						else
							a += (int)c;
						if (isSpace(temp))
							break;
						c = temp;
						fputc(stdout, temp);
					}
					fputc(stdout, '\n');
					*(int *)va_arg(ap, int *) = a;
					count++;
					break;
				}
				case 'f':
				{
					char *buff = (char *)malloc(sizeof(char) * 50);
					gets(buff);
					*(float *)va_arg(ap, float *) = (float)atof(buff);
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
