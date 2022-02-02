/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:54:29 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 17:54:31 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_uarg(t_options o, va_list list)
{
	if (o.typesize == 2)
		return (va_arg(list, unsigned long long));
	else if (o.typesize == 1)
		return ((unsigned long)va_arg(list, unsigned long long));
	else if (o.typesize == 0)
		return ((unsigned int)va_arg(list, unsigned long long));
	else if (o.typesize == -1)
		return ((unsigned short)va_arg(list, unsigned long long));
	else
		return ((unsigned char)va_arg(list, unsigned long long));
}

long long			get_iarg(t_options o, va_list list)
{
	if (o.typesize == 2)
		return (va_arg(list, long long));
	else if (o.typesize == 1)
		return ((long)va_arg(list, long long));
	else if (o.typesize == 0)
		return ((int)va_arg(list, long long));
	else if (o.typesize == -1)
		return ((short)va_arg(list, long long));
	else
		return ((char)va_arg(list, long long));
}

long long			give_totalprinted(t_options o, va_list list, int tp)
{
	long long	*n;

	n = va_arg(list, long long *);
	if (o.typesize == 2)
		*n = tp;
	else if (o.typesize == 1)
		*(long *)n = tp;
	else if (o.typesize == 0)
		*(int *)n = tp;
	else if (o.typesize == -1)
		*(short *)n = tp;
	else
		*(char *)n = tp;
	return (0);
}

wchar_t				*get_wcsarg(va_list list)
{
	wchar_t	*wcs;

	wcs = va_arg(list, wchar_t *);
	if (wcs == NULL)
		wcs = L"(null)";
	return (wcs);
}

char				*get_sarg(va_list list)
{
	char	*s;

	s = va_arg(list, char *);
	if (s == NULL)
		s = "(null)";
	return (s);
}
