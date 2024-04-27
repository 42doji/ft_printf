/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_iii.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:09:51 by doji              #+#    #+#             */
/*   Updated: 2024/04/27 19:10:18 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	_error_handler(int flag, char *s)
{
	if (flag == FLAG_P && !s)
		return (_putstr("(nil)"));
	else if (flag == FLAG_S && !s)
		return (_putstr("(null)"));
	else
		return (_putstr(s));
	return (0);
}

char	num_to_hex(int n, int flag)
{
	if (n < 10)
		return (n + '0');
	else
	{
		if (flag)
			return (n - 10 + 'A');
		else
			return (n - 10 + 'a');
	}
}

int	address_len(unsigned long long n)
{
	int	res;

	res = 0;
	while (n)
	{
		n /= 16;
		res++;
	}
	return (res);
}
