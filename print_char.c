/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:54:37 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 17:56:50 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		wcharlen(const wchar_t c)
{
	if (c < 0x80)
		return (1);
	else if (c < 0x0800)
		return (2);
	else if (c < 0x010000)
		return (3);
	else
		return (4);
}

long long	print_char(t_options o, va_list list, char typechar)
{
	wchar_t			c;
	unsigned int	clen;

	if (typechar == 'c')
		c = va_arg(list, wchar_t);
	else
		c = typechar;
	clen = (o.typesize == 1) ? wcharlen(c) : 1;
	if (!o.width || o.widthvalue < clen)
		o.widthvalue = clen;
	if (!o.left)
		pad(0, o.widthvalue - clen, o);
	if (o.typesize != 1)
		ft_putchar(c);
	else
		print_unicode(c);
	if (o.left)
		pad(0, o.widthvalue - clen, o);
	return (o.widthvalue);
}

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t		ft_wcslen(const wchar_t *s, int prec)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s[i] && (prec < 0 || ((int)(res + wcharlen(s[i])) <= prec)))
	{
		res += wcharlen(s[i]);
		i++;
	}
	return (res);
}

long long	print_string(t_options o, va_list list)
{
	wchar_t			*wcs;
	char			*s;
	unsigned int	slen;

	if (o.typesize == 1)
		wcs = get_wcsarg(list);
	else
		s = get_sarg(list);
	slen = (o.typesize == 1) ? ft_wcslen(wcs, -1) : ft_strlen(s);
	if (!o.prec || (unsigned int)o.precvalue > slen)
		o.precvalue = slen;
	if (o.prec && o.typesize == 1 &&
		(unsigned int)o.precvalue > ft_wcslen(wcs, o.precvalue))
		o.precvalue = ft_wcslen(wcs, o.precvalue);
	if (!o.width || o.widthvalue < o.precvalue)
		o.widthvalue = o.precvalue;
	if (!o.left)
		pad(0, o.widthvalue - o.precvalue, o);
	if (o.typesize != 1)
		write(1, s, o.precvalue);
	else
		print_wcs(wcs, o);
	if (o.left)
		pad(0, o.widthvalue - o.precvalue, o);
	return (o.widthvalue);
}
