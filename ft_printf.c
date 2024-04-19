/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_stdarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:55:57 by doji              #+#    #+#             */
/*   Updated: 2024/04/19 20:12:37 by doji             ###   ########.fr       */
/*                                                                            */
/* **************************045   37    25    %  ************************************************ */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum
{
	FLAG_ERR = -1,
	FLAG_C = 0,
	FLAG_S = 1,
	FLAG_P = 2,
	FLAG_D = 3,
	FLAG_I = 4,
	FLAG_U = 5,
	FLAG_X = 6,
	FLAG_XX = 7,
	FLAG_PCNT = 8,
	FLAG_N = 9	
} Conversion;

typedef struct s_node
{
	void		*data;
	struct s_node	*next;
	Conversion conv;
} t_node;

int	_conversion_check(char c)
{
	const char *flags = "cspdiuxX%";
	int		i;

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

void	_putchar(int c)
{
	write(1, &c, 1);
}

void	_putstr(const char *s)
{
	while (s && *s)
		_putchar(*(s++));
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

void	lld_to_hex(void *address, int flag)
{
	char			s[19];
	int			i;
	int			j;
	unsigned long long	n;
	char			numb;
	int			num_flag;

	num_flag = 0;
	i = 0;
	j = 2;
	n = (unsigned long long)address;
	s[0] = '0';
	s[1] = 'X';
	while (i < 16)
	{
		numb = num_to_hex((n >> (4 * (15 - i))) & 0xF, flag);
		if (numb > '0')
			num_flag = 1;
		if (num_flag)
			s[j++] = numb;
		i++;
	}
	s[i + 2] = '\0';
	_putstr(s);
}

void	int_to_hex(int n, int flag)
{
	char			s[11];
	int			i;
	int			j;
	char			numb;
	int			num_flag;

	num_flag = 0;
	i = 0;
	j = 0;
	while (i < 8)
	{
		numb = num_to_hex((n >> (4 * (7 - i))) & 0xF, flag);
		if (numb > '0')
			num_flag = 1;
		if (num_flag)
			s[j++] = numb;
		i++;
	}
	s[i] = '\0';
	_putstr(s);
}

int	_count_conversions(const char *s)
{
	int	conversions;
	int	flag;
	int	i;

	conversions = 0;
	flag = 0;
	i = 0;
	if (_strlen(s) < 2)
		return (0);
	while (s[i] != '\0')
	{
		if (flag && (_conversion_check(s[i]) >= 0))
		{
			flag = 0;
			conversions++;
			i++;
			if (s[i] == '\0')
				break;
		}
		if (!flag && _is_percent(s[i]))
		{
			flag = 1;
			if (!s[i + 1] || _conversion_check(s[i]) < 0)
				return (-1);
		}
		i++;
	}
	return (conversions);
}

int	_error_handler(void)
{
	const char *s = "wrong input\n";
	
	_putstr(s);
	return (0);
}

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

void	_itoa(int n)
{
	if (n == -2147483648)
		_putstr("-2147483648");
	if (n < 0)
	{
		_putchar('-');
		n = -n;
	}
	else if (n > 10)
	{
		_itoa(n / 10);
		_itoa(n % 10);
	}
	else if (n < 10)
		_putchar(n + '0');
}

void	_conv_handler(char c, va_list ap)
{
	int	conv_type;

	conv_type = _conversion_check(c);
	if (conv_type == FLAG_C)
		_putchar(va_arg(ap, int));
	else if (conv_type == FLAG_S)
		_putstr(va_arg(ap, char *));
	else if (conv_type == FLAG_P)
		lld_to_hex(va_arg(ap, void *), 0);
	else if (conv_type == FLAG_D)
		_itoa(va_arg(ap, int));
	else if (conv_type == FLAG_I)
		_itoa(va_arg(ap, int));	
	else if (conv_type == FLAG_X)
		int_to_hex(va_arg(ap, int), 0);
	else if (conv_type == FLAG_XX)
		int_to_hex(va_arg(ap, int), 1);
	else if (conv_type == FLAG_PCNT)
	{
		va_arg(ap, int);
		_putchar('%');
	}
}


int ft_printf(const char *s, ...)
{
	int	n;
	va_list	ap;

	n =_count_conversions(s);
       	if (n < 0)
		return (_error_handler());
	va_start(ap, n);
	while (n > 0 || s && *s)
	{
		if (_is_conversion(s) > 0)
		{
			_conv_handler(*(s + 1), ap);	
			n--;
			s++;
		}
		else if (_is_conversion(s) < 0)	
			return (_error_handler());
		else
			_putchar(*s);
		s++;
	}
	va_end(ap);
	return (n);
}

int main(void)
{
	ft_printf("%%\n");
	fflush(stdout);
	printf("%%\n");
	return (0);
}
