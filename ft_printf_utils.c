/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahn <hahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:24:33 by hahn              #+#    #+#             */
/*   Updated: 2022/03/16 15:53:30 by hahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
char	*ft_itoa(unsigned long long n)
{
	unsigned long long	temp;
	int					idx;
	char				*str;

	if (!n)
		return ("0");
	idx = 0;
	temp = n;
	while (temp)
	{
		idx++;
		temp /= 10;
	}
	str = (char *)malloc(sizeof(char) * (idx + 1));
	str[idx--] = '\0';
	while (n)
	{
		str[idx--] = n % 10;
		n /= 10;
	}
	return (str);
}
*/