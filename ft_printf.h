/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doji <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:00:30 by doji              #+#    #+#             */
/*   Updated: 2024/04/27 19:18:07 by doji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

enum {
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
} e_conversion;

int		_conversion_check(char c);
int		_strlen(const char *s);
int		_is_percent(char c);
int		_putchar(int c);
int		_putstr(const char *s);
int		_error_handler(int flag, char *s);
char	num_to_hex(int n, int flag);
int		lld_to_hex(unsigned long long n, int flag);
void	int_to_hex(unsigned int n, int flag, int *res);
int		_count_conversions(const char *s);
int		_is_conversion(const char *s);
void	_itoa(int n, int *i);
int		_conv_handler(char c, va_list ap, int *i);
int		ft_printf(const char *s, ...);
int		address_len_int(int n);
int		address_len(unsigned long long n);

#endif
