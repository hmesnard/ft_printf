/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:54:55 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 18:39:11 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	get_nblen(unsigned long long n)
{
	if (n < 10)
		return (1);
	return (1 + get_nblen(n / 10));
}

void			ft_putunbr(unsigned long long u)
{
	if (u >= 10)
		ft_putunbr(u / 10);
	ft_putchar(u % 10 + 48);
}

void			print_int2(long long n, t_options o,
							unsigned int nblen, int prefix)
{
	unsigned long long	posn;

	posn = (n < 0) ? -n : n;
	if (!o.left && !(o.zero && !o.prec))
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
	if (n < 0)
		write(1, "-", 1);
	else if (o.plus)
		write(1, "+", 1);
	else if (o.space)
		write(1, " ", 1);
	if (!o.left && o.zero && !o.prec)
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
	pad(1, o.precvalue - nblen, o);
	if (!(n == 0 && o.prec && o.precvalue == 0))
		ft_putunbr(posn);
	if (o.left)
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
}

long long		print_int(t_options o, va_list list)
{
	long long			n;
	unsigned long long	posn;
	unsigned int		nblen;
	int					prefix;

	n = get_iarg(o, list);
	posn = (n < 0) ? -n : n;
	nblen = get_nblen(posn);
	prefix = 0;
	if (n < 0 || o.plus || o.space)
		prefix = 1;
	if (n == 0 && o.prec && o.precvalue == 0)
		nblen = 0;
	if (!o.prec || (unsigned int)o.precvalue < nblen)
		o.precvalue = nblen;
	if (!o.width || o.widthvalue < (o.precvalue + prefix))
		o.widthvalue = (o.precvalue + prefix);
	print_int2(n, o, nblen, prefix);
	return (o.widthvalue);
}

long long		print_unsigned(t_options o, va_list list)
{
	unsigned long long	u;
	unsigned int		ulen;

	u = get_uarg(o, list);
	ulen = get_nblen(u);
	if (u == 0 && o.prec && o.precvalue == 0)
		ulen = 0;
	if (!o.prec || (unsigned int)o.precvalue < ulen)
		o.precvalue = ulen;
	if (!o.width || o.widthvalue < o.precvalue)
		o.widthvalue = o.precvalue;
	if (!o.left)
		pad(0, o.widthvalue - o.precvalue, o);
	pad(1, o.precvalue - ulen, o);
	if (!(u == 0 && o.prec && o.precvalue == 0))
		ft_putunbr(u);
	if (o.left)
		pad(0, o.widthvalue - o.precvalue, o);
	return (o.widthvalue);
}
