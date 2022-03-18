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
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	format_c(char c)
{
	return (write(1, &c, 1));
}

char	*base_maker(char format)
{
	if (format == 'u')
		return ("0123456789");
	else if (format == 'x' || format == 'p')
		return ("0123456789abcdef");
	else
		return ("0123456789ABCDEF");
}
int	format_di(int di)
{
	char	nbr[10];
	int		len;
	int		idx;

	len = 0;
	idx = 0;
	if (!di)
		return (write(1, "0", 1));
	if (di == -2147483648)
		return (write(1, "-2147483648", 11));
	if (di < 0)
	{
		di *= -1;
		len += write(1, "-", 1);
	}
	while (di)
	{
		nbr[idx++] = di % 10 + '0';
		di /= 10;
	}
	while (--idx != -1)
		len += write(1, &nbr[idx], 1);
	return (len);
}
int	format_uxp(unsigned long long uxp, char format)
{
	char	*base;
	char	nbr[16];
	int		div;
	int		idx;
	int		len;

	len = 0;
	idx = 0;
	base = base_maker(format);
	div = ft_strlen(base);
	if (!uxp)
		return (write(1, "0", 1));
	while (uxp)
	{
		nbr[idx++] = base[uxp % div];
		uxp /= div;
	}
	while (--idx != -1)
		len += write(1, &nbr[idx], 1);
	return (len);
}

int	format_p(unsigned long long p)
{
	write(1, "0x", 2);
	return (2 + format_uxp(p, 'p'));
}

int	contain_specific(va_list ap, const char *format)
{
	int	idx;
	int len;

	idx = -1;
	len = 0;
	while (format[++idx])
	{
		if (format[idx] == '%' && ++idx)
		{
			if (format[idx] == 'c')
				len += format_c(va_arg(ap, int));
			else if (format[idx] == 's')
				len += format_s(va_arg(ap, char *));
			else if (format[idx] == 'p')
				len += format_p(va_arg(ap, unsigned long long));
			else if (format[idx] == 'd' || format[idx] == 'i')
				len += format_di(va_arg(ap, int));
			else if (format[idx] == 'u' || format[idx] == 'x' || format[idx] == 'X')
				len += format_uxp(va_arg(ap, unsigned int), format[idx]);
			else if (format[idx] == '%')
				len += write(1, "%", 1);
		}
		else
			write(1, &format[idx], 1);
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