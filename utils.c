/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmesnard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:55:05 by hmesnard          #+#    #+#             */
/*   Updated: 2021/03/16 18:07:14 by hmesnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_atoi(const char *nptr, size_t *i)
{
	unsigned long long	nb;
	int					sign;

	nb = 0;
	sign = 1;
	while ((9 <= nptr[*i] && nptr[*i] <= 13) || nptr[*i] == ' ')
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
		if (nptr[(*i)++] == '-')
			sign = -1;
	while ('0' <= nptr[*i] && nptr[*i] <= '9')
	{
		nb = nb * 10 + (nptr[(*i)++] - 48);
		if (nb > INT_MAX)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
	}
	return (nb * sign);
}

void		pad(int zero, unsigned int padlen, t_options option)
{
	char	padchar;

	if ((option.zero && !option.prec) || zero)
		padchar = '0';
	else
		padchar = ' ';
	while (padlen-- > 0)
		ft_putchar(padchar);
}

long double	mypow(long double value, long long power)
{
	long double res;

	res = 1.0;
	if (power > 0)
		while (power-- != 0)
			res *= value;
	else
		while (power++ != 0)
			res /= value;
	return (res);
}
