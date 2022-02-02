/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:54:43 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/17 13:55:12 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_float3(t_floatinfo f, t_options o, int s)
{
	int digit;
	int e;

	f.dap = digits_after_point(f, o, s);
	e = (s <= 2 && f.ex < 0) ? 0 : f.ex;
	while ((s <= 2 && e >= 0) || (s >= 3 && e == f.ex) || f.dap > 0)
	{
		ft_putchar((digit = (int)(f.pos / mypow(10, e))) + 48);
		f.pos -= digit * mypow(10, e);
		if (((s <= 2 && !e) || (s >= 3 && e == f.ex)) && (f.dap > 0 || o.sharp))
			ft_putchar('.');
		if ((s <= 2 && e < 0) || (s >= 3 && e < f.ex))
			f.dap--;
		e--;
	}
	if (s >= 3)
	{
		if (f.ex < 0)
			write(1, "e-", 2);
		else
			write(1, "e+", 2);
		if (-10 < f.ex && f.ex < 10)
			write(1, "0", 1);
		ft_putunbr((f.ex < 0) ? -f.ex : f.ex);
	}
}

unsigned int	get_flen(t_floatinfo f, t_options o, int s)
{
	unsigned int	res;
	unsigned int	count;
	int				digit;
	int				e;

	count = 0;
	e = f.ex;
	if (s <= 2 && e < 0)
		e = 0;
	while ((s <= 2 && e >= 0) || (s == 3 && e == f.ex) || o.precvalue > 0)
	{
		count++;
		if (o.sharp || (digit = (int)(f.pos / mypow(10, e))) != 0
			|| (!(s == 2 && e < 0) && !(s == 4 && e < f.ex)))
			res = count;
		f.pos -= digit * mypow(10, e);
		if ((s == 1 && e < 0) || (s == 3 && e < f.ex)
			|| (s % 2 == 0 && e <= f.ex))
			o.precvalue--;
		e--;
	}
	if (!res)
		res++;
	return (res);
}

long long		print_float2(t_floatinfo f, t_options o, int s)
{
	f.f = arrondi(f, o, s);
	f.pos = (f.f < 0) ? -f.f : f.f;
	f.len = get_flen(f, o, s);
	if ((s <= 2 && (int)f.len > ((f.ex >= 0) ? f.ex + 1 : 1))
		|| (s >= 3 && f.len > 1) || o.sharp)
		f.len++;
	if (s >= 3)
		f.len += (f.ex <= -100 || 100 <= f.ex) ? 5 : 4;
	f.prefix = 0;
	if (f.f < 0 || 1 / f.f < 0 || o.plus || o.space)
		f.prefix = 1;
	if (!o.width || o.widthvalue < (f.len + f.prefix))
		o.widthvalue = f.len + f.prefix;
	if (!o.left && !o.zero)
		pad(0, o.widthvalue - (f.len + f.prefix), o);
	print_float_sign(f, o);
	if (!o.left && o.zero)
		pad(1, o.widthvalue - (f.len + f.prefix), o);
	print_float3(f, o, s);
	if (o.left)
		pad(0, o.widthvalue - (f.len + f.prefix), o);
	return (o.widthvalue);
}

long long		print_nan_inf(t_floatinfo f, t_options o, char *s)
{
	f.prefix = 0;
	o.zero = 0;
	if (f.f == f.f && (f.f < 0 || o.plus || o.space))
		f.prefix = 1;
	if (!o.width || o.widthvalue < (3 + f.prefix))
		o.widthvalue = 3 + f.prefix;
	if (!o.left)
		pad(0, o.widthvalue - (3 + f.prefix), o);
	if (f.f == f.f)
		print_float_sign(f, o);
	write(1, s, 3);
	if (o.left)
		pad(0, o.widthvalue - (3 + f.prefix), o);
	return (o.widthvalue);
}

long long		print_float(t_options o, va_list list, char typechar)
{
	t_floatinfo	f;

	f.f = va_arg(list, double);
	if (f.f != f.f || f.f < -DBL_MAX || f.f > DBL_MAX)
	{
		o.prec = 0;
		if (f.f != f.f)
			return (print_nan_inf(f, o, "nan"));
		else
			return (print_nan_inf(f, o, "inf"));
	}
	if (!o.prec)
		o.precvalue = 6;
	else if (o.precvalue == 0 && typechar == 'g')
		o.precvalue = 1;
	f.ex = exponent(f, o, typechar);
	if (typechar == 'f')
		return (print_float2(f, o, 1));
	else if (typechar == 'e')
		return (print_float2(f, o, 3));
	else if (-4 <= f.ex && f.ex < o.precvalue)
		return (print_float2(f, o, 2));
	else
		return (print_float2(f, o, 4));
}
