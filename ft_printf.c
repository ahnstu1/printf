/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 09:28:02 by hahn              #+#    #+#             */
/*   Updated: 2022/04/04 15:12:28 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	contain_specific(va_list ap, const char *format)
{
	int	len;

	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (*++format == 'c')
				len += format_c(va_arg(ap, int));
			else if (*format == 's')
				len += format_s(va_arg(ap, char *));
			else if (*format == 'p')
				len += format_uxp(va_arg(ap, unsigned long long), *format);
			else if (*format == 'd' || *format == 'i')
				len += format_di(va_arg(ap, int));
			else if (*format == 'u' || *format == 'x' || *format == 'X')
				len += format_uxp(va_arg(ap, unsigned int), *format);
			else if (*format == '%')
				len += write(1, "%", 1);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	str_len;
	int		idx;

	idx = 0;
	va_start(ap, format);
	str_len = contain_specific(ap, format);
	va_end(ap);
	return (str_len);
}
