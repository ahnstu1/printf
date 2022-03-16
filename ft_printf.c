/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:28:02 by hahn              #+#    #+#             */
/*   Updated: 2022/03/16 15:41:39 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	output;

	output = 0;
	while (*s++)
		output++;
	return (output);
}


int	format_s(char *s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else if (!*s)
		return (0);
	else
		write(1, s, ft_strlen(s));
	return ft_strlen(s);
}

int	format_c(char c)
{
	write(1, &c, 1);
	return (1);
}

int	format_p(unsigned long long p)
{
	char	hex[8];
	char	*base;
	int		idx;
	int		len;
	
	base = "0123456789abcdef";
	idx = 0;
	write(1, "0x", 2);
	while (p)
	{
		hex[idx++] = base[p % 16];
		p /= 16;
	}
	len = --idx;
	while (idx != -1)
		write(1, &hex[idx--], 1);

	return (len);
}

int	format_di(int di)
{
	int		nbr[10];
	int		idx;
	int		len;

	if (!di)
	{
		write (1, "0", 1);
		return (1);
	}
	else if (di = -2147483648)
	{
		write (1, "-2147483647", 11);
		return (11);
	}
	else
	{
		if (di < 0)
			di * -1;
		
	}
	return (len);
}

int	format_u(unsigned int u)
{
	int	nbr[10];
	int	idx;
	int	len;

	len = 0;
	idx = 0;
	while (u)
	{
		nbr[idx++] = u % 10;
		u /= 10;
	}
	len += --idx;
	while (idx != -1)
		write(1, &nbr[idx--] + '0', 1);
	return (len);
}

int	format_x(unsigned int x)
{
	char	hex[8];
	char	*base;
	int		idx;
	int		len;

	len = 0;
	base = "0123456789abcdef";
	idx = 0;
	while (x)
	{
		hex[idx++] = base[x % 16];
		x /= 16;
	}
	len += --idx;
	while (idx != -1)
		write(1, &hex[idx--], 1);
	return (len);
}

int	format_X(unsigned int X)
{
	char	hex[8];
	char	*base;
	int		idx;
	int		len;
	
	len = 0;
	base = "0123456789ABCDEF";
	idx = 0;
	while (X)
	{
		hex[idx++] = base[X % 16];
		X /= 16;
	}
	len += --idx; 
	while (idx != -1)
		write(1, &hex[idx--], 1);
	return (len);
}

int	contain_specific(va_list ap, const char *format)
{
	int	idx;
	int len;

	idx = 0;
	len = 0;
	while (format[idx])
	{
		if (format[idx] == '%')
		{
			idx++;
			if (format[idx] == 'c')
				len += format_c(va_arg(ap, int));
			else if (format[idx] == 's')
				len += format_s(va_arg(ap, char *));
			else if (format[idx] == 'p')
				len += format_p(va_arg(ap, unsigned long long));
			else if (format[idx] == 'd' || format[idx] == 'i')
				len += format_di(va_arg(ap, int));
			else if (format[idx] == 'u')
				len += format_u(va_arg(ap, unsigned int));
			else if (format[idx] == 'x')
				len += format_x(va_arg(ap, unsigned int));
			else if (format[idx] == 'X')
				len += format_X(va_arg(ap, unsigned int));
			else if (format[idx] == '%')
			{
				write(1, "%", 1);
				len++;
			}
		}
		else
			write(1, &format[idx], 1);
		idx++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	size_t	str_len;
	int		idx;

	idx = 0;
	str_len = 0;
	va_start(ap, format);
	while (format[idx])
	{
		if (format[idx] != '%')
			str_len++;
		if (format[idx] == '%')
			idx++;
		idx++;
	}
	if (ft_strlen(format) == str_len)
		write(1, format, str_len);
	else
		str_len += contain_specific(ap, format);
	va_end(ap);
	return (str_len);
}

#include <stdio.h>

int	main(void)
{
	ft_printf("%d", 0);
	ft_printf(" %d", 1);
	ft_printf("%d ", -1);
	ft_printf(" %d ", -3);
	
}

