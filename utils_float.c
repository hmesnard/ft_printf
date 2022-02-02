/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:55:20 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 18:13:29 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		arrondi(t_floatinfo f, t_options o, int s)
{
	int	dtr;

	if (s == 1 || s == 'f')
		dtr = o.precvalue;
	else if (s == 3 || s == 'e')
		dtr = o.precvalue - f.ex;
	else
		dtr = o.precvalue - (f.ex + 1);
	if (f.f > 0 &&
!(dtr == 0 && (long long)f.f % 2 == 0 && (f.f - (long long)f.f) * 10 - 5 == 0))
		return (f.f + 5 / (mypow(10, dtr + 1)));
	else if (f.f < 0 &&
!(dtr == 0 && (long long)f.f % 2 == 0 && (f.f - (long long)f.f) * 10 + 5 == 0))
		return (f.f - 5 / (mypow(10, dtr + 1)));
	else
		return (f.f);
}

unsigned int	digits_after_point(t_floatinfo f, t_options o, int s)
{
	unsigned int res;

	res = f.len;
	if (s >= 3)
		res -= (f.ex <= -100 || 100 <= f.ex) ? 6 : 5;
	else
		res -= ((f.ex > 0) ? (f.ex + 1) : 1);
	if (res > 1 || o.sharp)
		res--;
	return (res);
}

void			print_float_sign(t_floatinfo f, t_options o)
{
	if (f.f < 0 || 1 / f.f < 0)
		write(1, "-", 1);
	else if (o.plus)
		write(1, "+", 1);
	else if (o.space)
		write(1, " ", 1);
}

int				exponent(t_floatinfo f, t_options o, char typechar)
{
	int			res;
	t_floatinfo	tempf;

	tempf.f = f.f;
	res = 0;
	if (f.f <= -1.0 || 1.0 <= f.f)
		while (f.f <= -10.0 || 10.0 <= f.f)
		{
			f.f /= 10;
			res++;
		}
	else if (-1.0 < f.f && f.f < 1.0 && f.f != 0.0)
		while (-1.0 < f.f && f.f < 1.0)
		{
			f.f *= 10;
			res--;
		}
	tempf.ex = res;
	tempf.f = arrondi(tempf, o, typechar);
	tempf.pos = (tempf.f < 0) ? -tempf.f : tempf.f;
	if ((int)(tempf.pos / mypow(10, tempf.ex)) == 10)
		res++;
	else if ((int)(tempf.pos / mypow(10, tempf.ex)) == 0 && tempf.pos != 0.0)
		res--;
	return (res);
}
