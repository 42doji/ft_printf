/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:07:44 by doji              #+#    #+#             */
/*   Updated: 2024/04/27 18:46:57 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	_conversion_check(char c)
{
	const char	*flags = "cspdiuxX%";
	int			i;

	i = 0;
	while (flags[i])
	{
		if (c == flags[i])
			return (i);
		i++;
	}
	return (-1);
}

int	_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	_is_percent(char c)
{
	if (c == '%')
		return (1);
	return (0);
}

int	_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	_putstr(const char *s)
{
	char	*head;

	head = (char *)s;
	while (head && *head)
		_putchar(*(head++));
	return (_strlen(s));
}
