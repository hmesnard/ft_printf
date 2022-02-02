/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:55:14 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 18:45:51 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_unicode2(wchar_t c, char str[], size_t *size)
{
	if (c < 0x010000)
	{
		str[0] = ((c >> 12) & 0x0F) | 0xE0;
		str[1] = ((c >> 6) & 0x3F) | 0x80;
		str[2] = ((c >> 0) & 0x3F) | 0x80;
		*size = 3;
	}
	else if (c < 0x110000)
	{
		str[0] = ((c >> 18) & 0x07) | 0xF0;
		str[1] = ((c >> 12) & 0x3F) | 0x80;
		str[2] = ((c >> 6) & 0x3F) | 0x80;
		str[3] = ((c >> 0) & 0x3F) | 0x80;
		*size = 4;
	}
}

void		print_unicode(wchar_t c)
{
	char	str[4];
	size_t	size;

	size = 0;
	if (c < 0x80)
	{
		str[0] = ((c >> 0) & 0x7F) | 0x00;
		size = 1;
	}
	else if (c < 0x0800)
	{
		str[0] = ((c >> 6) & 0x1F) | 0xC0;
		str[1] = ((c >> 0) & 0x3F) | 0x80;
		size = 2;
	}
	else
		print_unicode2(c, str, &size);
	write(1, str, size);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		print_wcs(const wchar_t *s, t_options o)
{
	size_t	i;
	int		written;

	i = 0;
	written = 0;
	while (s[i] != L'\0' && (written += wcharlen(s[i])) <= o.precvalue)
		print_unicode(s[i++]);
}
