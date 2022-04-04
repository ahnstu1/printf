/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:45:48 by hahn              #+#    #+#             */
/*   Updated: 2022/04/04 15:12:40 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (format == 'p')
		len += write(1, "0x", 2);
	if (!uxp)
		len += (write(1, "0", 1));
	while (uxp)
	{
		nbr[idx++] = base[uxp % div];
		uxp /= div;
	}
	while (--idx != -1)
		len += write(1, &nbr[idx], 1);
	return (len);
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
