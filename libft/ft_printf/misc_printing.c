/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_printing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:42:02 by sbalcort          #+#    #+#             */
/*   Updated: 2017/10/31 19:44:22 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**print_unsigned
**pulls from va_arg then type casts.
**accounts for exceptions
**prints leading spaces, zeroes, number then space again.
*/

void			print_unsigned(t_flags *flags, va_list *arg, int base)
{
	uintmax_t	nbr;
	int			zeroes;
	int			spaces;

	spaces = 0;
	nbr = va_arg(*(arg), uintmax_t);
	nbr = typecast_unum(flags, nbr);
	zeroes = zeroes_unsigned(flags, nbr, base);
	spaces = flags->width - ft_numlen_ull(nbr, base) - zeroes;
	if (flags->flag & HASH && flags->data_type == 3)
		zeroes--;
	if (nbr == 0 && flags->precision == 0)
		spaces++;
	if ((flags->flag & HASH && flags->data_type == 6) || flags->data_type == 7)
		spaces = spaces - 2;
	else if (flags->flag & HASH && flags->data_type == 3)
		spaces--;
	while (!(flags->flag & MINUS) && spaces-- > 0)
		ft_putchar_mem(flags, ' ');
	print_prefix(flags, nbr);
	while (zeroes-- > 0)
		ft_putchar_mem(flags, '0');
	ft_putunbr_mem(flags, nbr, base);
	while (flags->flag & MINUS && spaces-- > 0)
		ft_putchar_mem(flags, ' ');
}

/*
**zeroes_signed && zeroes_unsigned
**determines leading width from precisison
**else uses width instead
**(unsigned) makes exeption for HASH or # for 0x prefix
**returns number of 0s for padding
*/

int				zeroes_signed(t_flags *flags, intmax_t nbr, int base)
{
	int			zeroes;

	zeroes = 0;
	if (flags->precision >= ft_numlen_ll(nbr, base))
		zeroes = flags->precision - ft_numlen_ll(nbr, base);
	else if (flags->flag & ZERO && flags->width > 0 && !(flags->flag & MINUS))
	{
		zeroes = flags->width - ft_numlen_ll(nbr, base);
		if (nbr < 0 || flags->flag & PLUS || flags->flag & SPACE)
			zeroes--;
	}
	return (zeroes);
}

int				zeroes_unsigned(t_flags *flags, uintmax_t nbr, int base)
{
	int			zeroes;

	zeroes = 0;
	if (flags->precision >= ft_numlen_ull(nbr, base))
		zeroes = flags->precision - ft_numlen_ull(nbr, base);
	else if (flags->flag & ZERO && flags->width > 0 && !(flags->flag & MINUS))
	{
		zeroes = flags->width - ft_numlen_ull(nbr, base);
		if ((flags->flag & HASH && flags->data_type == 6)
				|| flags->data_type == 7)
			zeroes = zeroes - 2;
		else if (flags->flag & HASH && flags->data_type == 3)
			zeroes--;
	}
	return (zeroes);
}

/*
**print_prefix
**given oOxXp and HASH prints leading 0x or 0X
*/

void			print_prefix(t_flags *flags, uintmax_t nbr)
{
	if ((flags->flag & HASH && nbr != 0) || flags->data_type == 7)
	{
		if (flags->data_type == 3 || flags->data_type == 6
				|| flags->data_type == 7)
			ft_putchar_mem(flags, '0');
		if (flags->data_type == 6 || flags->data_type == 7)
			(flags->caps == true) ?
				ft_putchar_mem(flags, 'X') : ft_putchar_mem(flags, 'x');
	}
}
