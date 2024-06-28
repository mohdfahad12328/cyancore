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

int vscanf(const FILE *dev, const char *fmt, va_list args)
{
	int ret = 0;
	int l_ret;
	int N;
	char c;
	while (*fmt != '\0')
	{
		l_ret = 0;
		if (*fmt == '%')
		{
			fmt++;
loop:
			switch (*fmt)
			{
				case 'i':
				case 'd':
				{
					int a = 0;
					N = 0;
					// skip leading whitespaces
					do
					{
						fgetc(dev, &c);
						if (c == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, c);
					} while (isSpace(c));
					// initialize first int digit
					if (c == '-')
						N = 1;
					else if (isDigit(c))
						a = c - '0';
					// append rest of digits till whitespace
					do
					{
						fgetc(dev, &c);
						if (isDigit(c))
						{
							a *= 10;
							a += (c - '0');
							fputc(stdout, c);
						}
						else if (a && (c == 0x7f || c== 0x08))
						{
							a /= 10;
							fputs(stdout, "\b \b");
						}
					} while (!isSpace(c));
					(c == '\r') ? fputc(stdout, '\n') : fputc(stdout, c);
					if (l_ret >= 2)
						*(int64_t *)va_arg(args, int64_t *) = (N) ? -(a) : a;
					else if (l_ret == 1)
						*(long *)va_arg(args, long *) = (N) ? -(a) : a;
					else
						*(int *)va_arg(args, int *) = (N) ? -(a) : a;
					ret++;
					break;
				}
				case 'l':
				{
					l_ret++;
					fmt++;
					goto loop;
				}
#if USE_FLOAT == 1
				case 'f':
				{
					float a = 0;
					unsigned int rp = 0; // radix point
					float e = 1;
					unsigned int fl = 1; // floating length - length after radix point
					N = 0;
					// skip leading whitespaces
					do
					{
						fgetc(dev, &c);
						if (c == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, c);
					} while (isSpace(c));
					if (c == '.')
						rp = 1;
					else if (c == '-')
						N = 1;
					else if (isDigit(c))
						a = (float)(c - '0');
					// append rest of digits till whitespace
					do
					{
						fgetc(dev, &c);
						if (!rp && c == '.')
						{
							rp = 1;
							fputc(stdout, c);
						}
						else if (isDigit(c))
						{
							if (rp)
							{
								e /= 10.0;
								a += (e * (float)(c - '0'));
								fl *= 10;
							}
							else
							{
								a *= 10.0;
								a += (float)(c - '0');
							}
							fputc(stdout, c);
						}
						else if (a && (c == 0x7f || c == 0x08))
						{
							long d = (long)a;
							float frac = a - (float)d;
							if (frac == 0.0 && rp)
								rp = 0;
							else if (rp)
							{
								fl /= 10;
								frac *= fl;
								frac = (long)frac / (float)fl;
								a = d + frac;
							}
							else
								a = (int)a / 10;
							fputs(stdout, "\b \b");
						}
					} while (!isSpace(c));
					(c == '\r') ? fputc(stdout, '\n') : fputc(stdout, c);
					*(float *)va_arg(args, float *) = (N) ? -(a) : a;
					ret++;
					break;
				}
#endif
				case 'c':
				{
					*(char *)va_arg(args, char *) = getchar();
					ret++;
					break;
				}
				case 's':
				{
					int i = 0;
					char *s = va_arg(args, char *);
					//skip leading whitespaces
					do
					{
						fgetc(dev, &c);
						if (c == '\r')
							fputc(stdout, '\n');
						else
							fputc(stdout, c);
					} while (isSpace(c));
					s[i++] = c;
					do
					{
						fgetc(dev, &c);
						if (isSpace(c))
							break;
						else if (i && (c == 0x7f || c == 0x08))
						{
							i--;
							fputs(stdout, "\b \b");
						}
						else
							s[i++] = c;
						fputc(stdout, c);
					} while (!isSpace(c));
					(c == '\r') ? fputc(stdout, '\n') : fputc(stdout, c);
					s[i] = '\0';
					ret++;
					break;
				}
				default:
					return -1;
			}
			continue;
		}
		/* increment pointer if % not found */
		fmt++;
	}
	fputc(stdout, '\n');
	return ret;
}

int scanf(const char *fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	ret = vscanf(stdin, fmt, va);
	va_end(va);
	return ret;
}
