/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_ii.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:08:50 by doji              #+#    #+#             */
/*   Updated: 2024/04/28 17:33:37 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	address_len_int(int n)
{
	int	res;

	res = 0;
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res);
}

int	lld_to_hex(unsigned long long n, int flag)
{
	char	buf[19];
	int		pos;
	int		digit;

	pos = 18;
	if (n == 0)
		return (_error_handler(FLAG_P, NULL));
	buf[pos] = '\0';
	while (n != 0)
	{
		digit = n % 16;
		buf[--pos] = num_to_hex(digit, flag);
		n /= 16;
	}
	buf[--pos] = 'x';
	buf[--pos] = '0';
	return (_putstr(&buf[pos]));
}

void	int_to_hex(unsigned int n, int flag, int *res)
{
	char	s[11];
	int		i;
	int		j;
	char	temp;

	i = address_len(n);
	j = 0;
	if (!i)
		*res += _putstr("0");
	else
	{
		s[i] = '\0';
		while (--i >= 0)
		{
			temp = num_to_hex(((n >> (4 * j++)) & 0xF), flag);
			s[i] = temp;
			if (i == 0)
				break ;
		}
		*res += _putstr(s);
	}
}
