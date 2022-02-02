/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:55:00 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 17:59:10 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	get_oclen(unsigned long long oc)
{
	if (oc < 8)
		return (1);
	return (1 + get_oclen(oc / 8));
}

void			ft_putocnbr(unsigned long long oc, t_options o)
{
	char *base;

	base = "01234567";
	if (oc >= 8)
		ft_putocnbr(oc / 8, o);
	ft_putchar(base[oc % 8]);
}

void			print_octal2(unsigned long long oc, t_options o, int prefix)
{
	unsigned int	oclen;

	oclen = get_oclen(oc);
	if (oc == 0 && o.prec && o.precvalue == 0)
		oclen = 0;
	if (!o.left && !(o.zero && !o.prec))
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
	if (prefix)
		write(1, "0", 1);
	if (!o.left && o.zero && !o.prec)
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
	pad(1, o.precvalue - oclen, o);
	if (!(oc == 0 && o.prec && o.precvalue == 0))
		ft_putocnbr(oc, o);
	if (o.left)
		pad(0, o.widthvalue - (o.precvalue + prefix), o);
}

long long		print_octal(t_options o, va_list list)
{
	unsigned long long	oc;
	unsigned int		oclen;
	int					prefix;

	oc = get_uarg(o, list);
	oclen = get_oclen(oc);
	prefix = 0;
	if (o.sharp && oc != 0 && (!o.prec || (unsigned int)o.precvalue <= oclen))
		prefix = 1;
	if (oc == 0 && o.prec && o.precvalue == 0 && !o.sharp)
		oclen = 0;
	if (!o.prec || (unsigned int)o.precvalue < oclen)
		o.precvalue = oclen;
	if (!o.width || o.widthvalue < (o.precvalue + prefix))
		o.widthvalue = (o.precvalue + prefix);
	print_octal2(oc, o, prefix);
	return (o.widthvalue);
}
