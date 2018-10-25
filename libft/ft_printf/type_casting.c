/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:39:23 by sbalcort          #+#    #+#             */
/*   Updated: 2017/10/31 19:41:04 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**These functions typecast and truncate the data from intmax_t
**down to what it needs to be. signed and unsigned
*/

intmax_t		typecast_num(t_flags *flags, intmax_t nbr)
{
	if (flags->length == 4 || (flags->caps == true && flags->data_type == 2))
		nbr = (long int)nbr;
	else if (flags->length == 0)
		nbr = (int)nbr;
	else if (flags->length == 1)
		nbr = (signed char)nbr;
	else if (flags->length == 2)
		nbr = (short int)nbr;
	else if (flags->length == 6)
		nbr = (size_t)nbr;
	return (nbr);
}

uintmax_t		typecast_unum(t_flags *flags, uintmax_t nbr)
{
	if (flags->data_type == 7)
		return (nbr);
	if (flags->length == 4 || (flags->caps == true && flags->data_type != 6))
		nbr = (unsigned long)nbr;
	else if (flags->length == 0)
		nbr = (unsigned int)nbr;
	else if (flags->length == 1)
		nbr = (unsigned char)nbr;
	else if (flags->length == 2)
		nbr = (unsigned short)nbr;
	else if (flags->length == 6)
		nbr = (size_t)nbr;
	return (nbr);
}
