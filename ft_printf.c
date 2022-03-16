#include "ft_printf.h"

void	format_s(char *str)
{
	write(1, str, ft_strlen(str));
	return ;
}

void	format_c(char c)
{
	write(1, &c, 1);
	return ;
}

void	format_p(unsigned long long add)
{
	write(1, "0x", 2);
}

void	contain_specific(va_list ap, char *format)
{
	int	idx;

	idx = 0;
	while (format[idx])
	{
		if (format[idx] == "%")
		{
			idx++;
			if (format[idx] == 'c')
				format_c(va_arg(ap, int));
			else if (format[idx] == 's')
				format_s(va_arg(ap, char *));
			else if (format[idx] == 'p')
				format_p(va_arg(ap, unsigned long long));
			else if (format[idx] == 'd' || format[idx] == 'i')
				format_di(va_arg(ap, int));
			else if (format[idx] == 'u')
				format_u(va_arg(ap, unsigned int));
			else if (format[idx] == 'x')
				format_x(va_arg(ap, unsigned int));
			else if (format[idx] == 'X')
				format_X(va_arg(ap, unsigned int));
			else if (format[idx] == '%')
				write(1, "%", 1);
		}
		else
			write(1, &format[idx], 1);
		idx++;
	}
	return ;
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	char	temp;
	int		str_len;

	str_len = 0;
	temp = format;
	va_start(ap, format);
	while (*format)
	{
		if (*format++ != "%")
			str_len++;
	}
	if (ft_strlen(format) == str_len)
		write(1, format, str_len);
	else
		contain_specific(ap, format);
	va_end(ap);
	return (str_len);
}
