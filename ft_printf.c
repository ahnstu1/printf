/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:28:02 by hahn              #+#    #+#             */
/*   Updated: 2022/03/16 14:29:49 by hahn             ###   ########.fr       */
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


void	format_s(char *s)
{
	if (!s)
		write(1, "(null)", 6);
/*	else if (!*s)
		return ;*/
	else
		write(1, s, ft_strlen(s));
	return ;
}

void	format_c(char c)
{
	write(1, &c, 1);
	return ;
}

void	format_p(unsigned long long p)
{
	char	hex[8];
	char	*base;
	int		idx;
	
	base = "0123456789abcdef";
	idx = 0;
	write(1, "0x", 2);
	while (p)
	{
		hex[idx++] = base[p % 16];
		p /= 16;
	}
	while (--idx != -1)
		write(1, &hex[idx], 1);

	return ;
}

void	format_di(int di)
{
	int		nbr[10];
	int		idx;
	char	output;

	if (!di)
	{
		write (1, "0", 1);
		return ;
	}
	idx = 0;
	if (di < 0)
		write(1, "-", 1);	
	while (di)
	{
		nbr[idx++] = di % 10;
		di /= 10;
	}
	while (--idx != -1)
	{
		if (nbr[idx] < 0)
			output = (nbr[idx] * -1) + '0';
		else
			output = nbr[idx] + '0';
		write(1, &output, 1);
	}
	return ;
}

void	format_u(unsigned int u)
{
	int	nbr[10];
	int	idx;

	idx = 0;
	while (u)
	{
		nbr[idx++] = u % 10;
		u /= 10;
	}
	while (--idx != -1)
		write(1, &nbr[idx] + '0', 1);
	return ;
}

void	format_x(unsigned int x)
{
	char	hex[8];
	char	*base;
	int		idx;

	base = "0123456789abcdef";
	idx = 0;
	while (x)
	{
		hex[idx++] = base[x % 16];
		x /= 16;
	}
	while (--idx != -1)
		write(1, &hex[idx], 1);
	return ;
}

void	format_X(unsigned int X)
{
	char	hex[8];
	char	*base;
	int		idx;
	
	base = "0123456789ABCDEF";
	idx = 0;
	while (X)
	{
		hex[idx++] = base[X % 16];
		X /= 16;
	}
	while (--idx != -1)
		write(1, &hex[idx], 1);
	return ;
}

void	contain_specific(va_list ap, const char *format)
{
	int	idx;

	idx = 0;
	while (format[idx])
	{
		if (format[idx] == '%')
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
	size_t	str_len;
	int		idx;

	idx = 0;
	str_len = 0;
	va_start(ap, format);
	while (format[idx])
	{
		if (format[idx] != '%')
			str_len++;
		if (format[idx] == '%' && format[idx + 1] == '%')
		{
			str_len++;
			idx++;
		}
		idx++;
	}
	if (ft_strlen(format) == str_len)
		write(1, format, str_len);
	else
		contain_specific(ap, format);
	va_end(ap);
	return (str_len);
}

#include <stdio.h>
/*
int	main(void)
{
	ft_printf("%s", "");
	ft_printf(" %s", "");
	ft_printf("%s ", "");
	ft_printf(" %s ", "");
	ft_printf(" %s ", "-");
	ft_printf(" %s %s ", "", "-");
	ft_printf(" %s %s ", " - ", "");
	ft_printf(" %s %s %s %s", " - ", "", "4", "");
	ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	ft_printf(" NULL %s NULL ", NULL);
}

*/