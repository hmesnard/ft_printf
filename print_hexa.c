/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:54:49 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 18:46:24 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	get_xlen(unsigned long long x)
{
	if (x < 16)
		return (1);
	return (1 + get_xlen(x / 16));
}

void			ft_putxnbr(unsigned long long x, t_options o, int maj)
{
	char *base;

	if (maj)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (x >= 16)
		ft_putxnbr(x / 16, o, maj);
	ft_putchar(base[x % 16]);
}

void			print_hexa2(unsigned long long x, t_options o,
							int prefix, int maj)
{
	unsigned int	xlen;

	xlen = get_xlen(x);
	if (x == 0 && o.prec && o.precvalue == 0)
		xlen = 0;
	if (!o.left && !(o.zero && !o.prec))
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
	if (prefix)
	{
		if (maj)
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
	if (!o.left && o.zero && !o.prec)
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
	pad(1, o.precvalue - xlen, o);
	if (!(x == 0 && o.prec && o.precvalue == 0))
		ft_putxnbr(x, o, maj);
	if (o.left)
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
}

long long		print_hexa(t_options o, va_list list, int maj)
{
	unsigned long long	x;
	unsigned int		xlen;
	int					prefix;

	x = get_uarg(o, list);
	xlen = get_xlen(x);
	prefix = 0;
	if (o.sharp && x != 0)
		prefix = 2;
	if (x == 0 && o.prec && o.precvalue == 0)
		xlen = 0;
	if (!o.prec || (unsigned int)o.precvalue < xlen)
		o.precvalue = xlen;
	if (!o.width || o.widthvalue < (o.precvalue + prefix))
		o.widthvalue = (o.precvalue + prefix);
	print_hexa2(x, o, prefix, maj);
	return (o.widthvalue);
}

long long		print_pointer(t_options o, va_list list)
{
	void			*p;
	unsigned int	plen;

	p = va_arg(list, void *);
	plen = get_xlen((unsigned long)p);
	if (p == 0 && o.prec && o.precvalue == 0)
		plen = 0;
	if (!o.prec || (unsigned int)o.precvalue < plen)
		o.precvalue = plen;
	if (!o.width || o.widthvalue < o.precvalue + 2)
		o.widthvalue = o.precvalue + 2;
	if (!o.left && !(o.zero && !o.prec))
		pad(0, o.widthvalue - (o.precvalue + 2), o);
	write(1, "0x", 2);
	if (!o.left && o.zero && !o.prec)
		pad(0, o.widthvalue - (o.precvalue + 2), o);
	pad(1, o.precvalue - plen, o);
	if (!(p == 0 && o.prec && o.precvalue == 0))
		ft_putxnbr((unsigned long)p, o, 0);
	if (o.left)
		pad(0, o.widthvalue - (o.precvalue + 2), o);
	return (o.widthvalue);
}
