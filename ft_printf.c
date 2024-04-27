/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:10:44 by doji              #+#    #+#             */
/*   Updated: 2024/04/27 18:48:08 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	_is_conversion(const char *s)
{
	int	i;

	i = 0;
	if (_is_percent(s[i]) && _conversion_check(s[i + 1]) >= 0)
		return (1);
	if (_is_percent(s[i]) && _conversion_check(s[i + 1]) < 0)
		return (-1);
	return (0);
}

void	_itoa(int n, int *i)
{
	if (n == -2147483648)
		*i += _putstr("-2147483648");
	else if (n < 0)
	{
		*i += _putchar('-');
		n = -n;
		_itoa(n, i);
	}
	else if (n >= 10)
	{
		_itoa(n / 10, i);
		_itoa(n % 10, i);
	}
	else if (n < 10)
		*i += _putchar(n + '0');
}

void	_itoa_u(unsigned int n, int *i)
{
	if (n >= 10)
	{
		_itoa(n / 10, i);
		_itoa(n % 10, i);
	}
	else if (n < 10)
		*i += _putchar(n + '0');
}

int	_conv_handler(char c, va_list ap, int *i)
{
	int	conv_type;

	conv_type = _conversion_check(c);
	if (conv_type == FLAG_C)
		*i += _putchar(va_arg(ap, int));
	else if (conv_type == FLAG_S)
		*i += _error_handler(FLAG_S, va_arg(ap, char *));
	else if (conv_type == FLAG_P)
		*i += lld_to_hex((unsigned long long)va_arg(ap, void *), 0);
	else if (conv_type == FLAG_D)
		_itoa(va_arg(ap, int), i);
	else if (conv_type == FLAG_I)
		_itoa(va_arg(ap, int), i);
	else if (conv_type == FLAG_U)
		_itoa_u(va_arg(ap, unsigned int), i);
	else if (conv_type == FLAG_X)
		int_to_hex(va_arg(ap, unsigned int), 0, i);
	else if (conv_type == FLAG_XX)
		int_to_hex(va_arg(ap, unsigned int), 1, i);
	else if (conv_type == FLAG_PCNT)
		return (*i += _putchar('%'));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	static int	i;
	int			n;
	va_list		ap;

	n = _count_conversions(s);
	va_start(ap, s);
	i = 0;
	while (n > 0 || (s && *s))
	{
		if (_is_conversion(s) > 0)
		{
			_conv_handler(*(s + 1), ap, &i);
			s++;
			n--;
		}
		else if (_is_conversion(s) < 0)
			return (-1);
		else
			i += _putchar(*s);
		if (*s)
			s++;
	}
	va_end(ap);
	return (i);
}
