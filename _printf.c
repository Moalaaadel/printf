#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

/**
 * _printf - prints formatted output
 * @format: format string
 *
 * Return: number of printed characters, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, count = 0;
	char c;
	char *str;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			write(1, &format[i], 1);
			count++;
			continue;
		}

		/* '%' is the last character */
		if (format[i + 1] == '\0')
		{
			va_end(args);
			return (-1);
		}

		i++;

		switch (format[i])
		{
		case 'c':
			c = (char)va_arg(args, int);
			write(1, &c, 1);
			count++;
			break;

		case 's':
			str = va_arg(args, char *);

			if (str == NULL)
				str = "(null)";

			write(1, str, strlen(str));
			count += strlen(str);
			break;

		case '%':
			write(1, "%", 1);
			count++;
			break;

		default:
			/* Unknown specifier */
			write(1, "%", 1);
			write(1, &format[i], 1);
			count += 2;
			break;
		}
	}

	va_end(args);

	return (count);
}
