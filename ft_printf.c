/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:53:45 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 17:54:14 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_w_p(t_options *o, const char *s, size_t *i, va_list list)
{
	if (s[*i] == '*' || ('0' <= s[*i] && s[*i] <= '9'))
	{
		o->width = 1;
		if (s[*i] == '*')
		{
			o->widthvalue = va_arg(list, int);
			(*i)++;
		}
		else
			o->widthvalue = ft_atoi(s, i);
	}
	if (s[*i] == '.')
	{
		o->prec = 1;
		(*i)++;
		if (s[*i] == '*')
		{
			o->precvalue = va_arg(list, int);
			(*i)++;
		}
		else if ('0' <= s[*i] && s[*i] <= '9')
			o->precvalue = ft_atoi(s, i);
		else
			o->precvalue = 0;
	}
}

t_options	get_option2(const char *s, size_t *i, va_list list, t_options o)
{
	get_w_p(&o, s, i, list);
	while (s[*i] == 'l' || s[*i] == 'h' || s[*i] == 'L')
	{
		if (s[*i] == 'l' && o.typesize < 2)
			o.typesize++;
		else if (s[*i] == 'h' && o.typesize > -2)
			o.typesize--;
		(*i)++;
	}
	if (o.width && o.widthvalue < 0)
	{
		o.left = 1;
		o.widthvalue = -o.widthvalue;
	}
	if (o.prec && o.precvalue < 0)
		o.prec = 0;
	if (o.left)
		o.zero = 0;
	if (o.plus)
		o.space = 0;
	return (o);
}

t_options	get_option(const char *s, size_t *i, va_list list)
{
	t_options	o;

	o.left = 0;
	o.zero = 0;
	o.plus = 0;
	o.space = 0;
	o.sharp = 0;
	o.width = 0;
	o.prec = 0;
	o.typesize = 0;
	while (s[++(*i)] == '-' || s[*i] == '0' || s[*i] == '+' || s[*i] == ' ' ||
			s[*i] == '#')
	{
		if (s[*i] == '-')
			o.left = 1;
		else if (s[*i] == '0')
			o.zero = 1;
		else if (s[*i] == '+')
			o.plus = 1;
		else if (s[*i] == ' ')
			o.space = 1;
		else
			o.sharp = 1;
	}
	return (get_option2(s, i, list, o));
}

long long	conversion(const char *s, size_t *i, va_list list, int tp)
{
	t_options	o;

	o = get_option(s, i, list);
	if (!s[*i])
		return (0);
	else if (s[*i] == 's')
		return (print_string(o, list));
	else if (s[*i] == 'p')
		return (print_pointer(o, list));
	else if (s[*i] == 'd' || s[*i] == 'i')
		return (print_int(o, list));
	else if (s[*i] == 'u')
		return (print_unsigned(o, list));
	else if (s[*i] == 'x' || s[*i] == 'X')
		return (print_hexa(o, list, (s[*i] == 'X') ? 1 : 0));
	else if (s[*i] == 'o')
		return (print_octal(o, list));
	else if (s[*i] == 'n')
		return (give_totalprinted(o, list, tp));
	else if (s[*i] == 'f' || s[*i] == 'g' || s[*i] == 'e')
		return (print_float(o, list, s[*i]));
	else
		return (print_char(o, list, s[*i]));
}

int			ft_printf(const char *s, ...)
{
	va_list	list;
	size_t	i;
	int		printed;

	va_start(list, s);
	printed = 0;
	while (s[(i = 0)])
	{
		while (s[i] && s[i] != '%')
			if (printed + ++i >= INT_MAX)
				return (-1);
		printed += write(1, s, i);
		if (s[i] == '%')
		{
			printed += conversion(s, &i, list, printed);
			if (s[i])
				i++;
		}
		s += i;
		if (printed >= INT_MAX)
			return (-1);
	}
	va_end(list);
	return ((int)printed);
}
