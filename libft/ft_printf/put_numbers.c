/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:39:42 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/01 16:44:25 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**From unsigned long long (unitmax_t) and base
**returns the number of digits to print
*/

int			ft_numlen_ull(uintmax_t value, unsigned int base)
{
	int		len;

	len = (value == 0) ? 1 : 0;
	while (value != 0)
	{
		value = value / base;
		len++;
	}
	return (len);
}

/*
**From long long (intmax_t) and base given
**Returns number of digits to print
*/

int			ft_numlen_ll(intmax_t value, int base)
{
	int		len;

	len = (value == 0) ? 1 : 0;
	while (value != 0)
	{
		value = value / base;
		len++;
	}
	return (len);
}

/*
**From long long (intmax_t) and power
**Return nbr^(power)
*/

intmax_t	ft_power_ll(intmax_t nbr, intmax_t power)
{
	intmax_t	tmp_nbr;

	tmp_nbr = nbr;
	if (power == 0)
		return (1);
	while (power-- > 1)
		nbr *= tmp_nbr;
	return (nbr);
}

/*
**From unsigned int max and power
**Return nbr^(power)
*/

uintmax_t	ft_power_ull(uintmax_t nbr, uintmax_t power)
{
	uintmax_t tmp_nbr;

	tmp_nbr = nbr;
	if (power == 0)
		return (1);
	while (power-- > 1)
		nbr *= tmp_nbr;
	return (nbr);
}

/*
**From struct flags and int max nbr
**Prints out leading char from - + ' '
*/

void		print_sign(t_flags *flags, intmax_t nbr)
{
	if (nbr < 0)
		ft_putchar_mem(flags, '-');
	else if (flags->flag & PLUS && nbr >= 0)
		ft_putchar_mem(flags, '+');
	else if (!(flags->flag & PLUS) && flags->flag & SPACE && nbr >= 0)
		ft_putchar_mem(flags, ' ');
}
