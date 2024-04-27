/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_ii.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:08:50 by doji              #+#    #+#             */
/*   Updated: 2024/04/27 18:52:16 by doji             ###   ########.fr       */
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
	static char			s[16];
	int					i;
	int					j;
	char				temp;
	unsigned long long	n2;

	n2 = n;
	temp = 0;
	if (n == 0)
		return (_error_handler(FLAG_P, NULL));
	i = address_len(n);
	_putstr("0x");
	s[i] = '\0';
	j = 0;
	while (--i >= 0)
	{
		temp = num_to_hex(((n2 >> (4 * j++)) & 0xF), flag);
		s[i] = temp;
	}
	return (_putstr(s) + 2);
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

int	_count_conversions(const char *s)
{
	static int	conversions;
	int			flag;
	int			i;

	flag = 0;
	i = -1;
	if (_strlen(s) < 2)
		return (0);
	while (s[++i] != '\0')
	{
		if (flag && (_conversion_check(s[i]) >= 0))
		{
			flag = 0;
			conversions++;
			if (s[++i] == '\0')
				break ;
		}
		if (!flag && _is_percent(s[i]))
		{
			flag = 1;
			if (!s[i + 1] || _conversion_check(s[i]) < 0)
				return (-1);
		}
	}
	return (conversions);
}
