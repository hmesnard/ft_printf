/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:54:22 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/17 15:44:30 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <float.h>
# include <wchar.h>
# include <limits.h>

/*
** conversion options
*/

typedef struct		s_options
{
	char			left;
	char			zero;
	char			plus;
	char			space;
	char			sharp;
	char			width;
	long long		widthvalue;
	char			prec;
	int				precvalue;
	char			typesize;
}					t_options;

/*
** floating point number informations
*/

typedef struct		s_floatinfo
{
	long double		f;
	long double		pos;
	int				ex;
	int				prefix;
	unsigned int	len;
	unsigned int	dap;
}					t_floatinfo;

/*
** ft_printf.c
*/

int					ft_printf(const char *s, ...);

/*
** get_args.c
*/

unsigned long long	get_uarg(t_options o, va_list list);
long long			get_iarg(t_options o, va_list list);
long long			give_totalprinted(t_options o, va_list list, int tp);
wchar_t				*get_wcsarg(va_list list);
char				*get_sarg(va_list list);

/*
** print_int.c
*/

void				ft_putunbr(unsigned long long u);
long long			print_int(t_options o, va_list list);
long long			print_unsigned(t_options o, va_list list);

/*
** print_char.c
*/

size_t				wcharlen(const wchar_t c);
long long			print_char(t_options o, va_list list, char typechar);
long long			print_string(t_options o, va_list list);

/*
** utils_char.c
*/

void				print_unicode(wchar_t c);
void				ft_putchar(char c);
void				print_wcs(const wchar_t *s, t_options o);

/*
** print_hexa.c
*/

long long			print_hexa(t_options o, va_list list, int maj);
long long			print_pointer(t_options o, va_list list);

/*
** print_octal.c
*/

long long			print_octal(t_options o, va_list list);

/*
** print_float.c
*/

long long			print_float(t_options o, va_list list, char typechar);

/*
** utils_float.c
*/

long double			arrondi(t_floatinfo f, t_options o, int s);
unsigned int		digits_after_point(t_floatinfo f, t_options o, int s);
void				print_float_sign(t_floatinfo f, t_options o);
int					exponent(t_floatinfo f, t_options o, char typechar);

/*
** utils.c
*/

int					ft_atoi(const char *nptr, size_t *i);
void				pad(int zero, unsigned int padlen, t_options option);
long double			mypow(long double value, long long power);

#endif
