/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:42:31 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/01 16:45:42 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** This prints out a signed number
** From front to back. Thats why it looks so weird.
** also keeps track of tailing zeroes
*/

void		ft_putnbr_mem(t_flags *flags, intmax_t nbr, int base)
{
	int			isneg;
	uintmax_t	power;

	isneg = (nbr < 0) ? -1 : 1;
	power = ft_power_ll(base, ft_numlen_ll(nbr, base));
	power = power / base;
	while (nbr != 0 && power != 0)
	{
		ft_putchar_mem(flags, ((nbr * isneg) / power) + '0');
		nbr = nbr - isneg * ((nbr * isneg) / power) * power;
		power = power / base;
	}
	while (nbr == 0 && power > 0)
	{
		if (flags->precision != 0)
			ft_putchar_mem(flags, '0');
		power = power / base;
	}
}

/*
** ft_putunbr_mem
** Also prints number from the front
** also prints alpha char for hex
*/

void		ft_putunbr_mem(t_flags *flags, uintmax_t nbr, int base)
{
	int			alpha;
	uintmax_t	power;

	alpha = (flags->caps == true) ? '7' : 'W';
	power = ft_power_ull(base, (ft_numlen_ull(nbr, base) - 1));
	while (nbr != 0 && power != 0)
	{
		if ((nbr / power) > 9)
			ft_putchar_mem(flags, (nbr / power) + alpha);
		else
			ft_putchar_mem(flags, (nbr / power) + '0');
		nbr = nbr - (nbr / power) * power;
		power = power / base;
	}
	while (nbr == 0 && power > 0)
	{
		if (flags->precision != 0 || (flags->flag & HASH
					&& flags->data_type == 3))
			ft_putchar_mem(flags, '0');
		power = power / base;
	}
}

/*
**Prints all chars
**also keeps track of the number printed for return
*/

void		ft_putchar_mem(t_flags *flags, char c)
{
	write(1, &c, 1);
	flags->written_chars++;
}
