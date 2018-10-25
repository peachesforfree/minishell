/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 13:26:29 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/01 16:46:00 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	sets width from number, if no nbr checks for precision
**	This handles the '.' precision and following number for width precision
*/

void		check_width_precision(const char *format, t_flags *flags)
{
	flags->width = 0;
	flags->precision = -1;
	if (ft_isdigit(format[flags->index]))
		flags->width = ft_atoi(&format[flags->index]);
	while (flags->width != 0 && ft_isdigit(format[flags->index]))
		flags->index++;
	if (format[flags->index] == '.')
	{
		flags->precision = 0;
		flags->index++;
	}
	if (ft_isdigit(format[flags->index]))
		flags->precision = ft_atoi(&format[flags->index]);
	while (flags->precision != -1 && ft_isdigit(format[flags->index]))
		flags->index++;
}

/*
**	sets numeric number code for each
**	length specifier
**	h = 2 hh = 1
**	l = 4 ll = 3
**	j = h z = 6
*/

void		check_length(const char *format, t_flags *flags)
{
	char *str;

	str = (char*)format;
	flags->length = 0;
	while (str[flags->index] == 'h' || str[flags->index] == 'l' ||
			str[flags->index] == 'j' || str[flags->index] == 'z')
	{
		if (str[flags->index] == 'h' && str[flags->index + 1] == 'h')
			flags->length = 1;
		else if (str[flags->index] == 'h' && str[flags->index + 1] != 'h')
			flags->length = 2;
		else if (str[flags->index] == 'l' && str[flags->index + 1] == 'l')
			flags->length = 3;
		else if (str[flags->index] == 'l' && str[flags->index + 1] != 'l')
			flags->length = 4;
		else if (str[flags->index] == 'j')
			flags->length = 5;
		else if (str[flags->index] == 'z')
			flags->length = 6;
		if (flags->length == 1 || flags->length == 3)
			flags->index++;
		if (flags->length != 0)
			flags->index++;
	}
}

/*
**Unless of conversion oOxXp
**base is automatically set for 10
*/

void		set_base(char format, t_flags *flags)
{
	flags->base = 10;
	if (format == 'o' || format == 'O')
		flags->base = 8;
	if (format == 'x' || format == 'X')
		flags->base = 16;
	if (format == 'p')
		flags->base = 16;
}

/*
**	checks for conversion flag "sSpdDioOuUxXcC"
**	then sets number code which isused in dispatch table
*/

int			check_conversion(char format, t_flags *flags)
{
	int i;

	i = 0;
	if (format == 'c' || format == 'C')
		i = 1;
	else if (format == 'd' || format == 'i' || format == 'D')
		i = 2;
	else if (format == 'o' || format == 'O')
		i = 3;
	else if (format == 's' || format == 'S')
		i = 4;
	else if (format == 'u' || format == 'U')
		i = 5;
	else if (format == 'x' || format == 'X')
		i = 6;
	else if (format == 'p')
		i = 7;
	else if (format)
	{
		flags->invalid_spec = format;
		i = 8;
	}
	flags->caps = (format >= 'A' && format <= 'Z') ? true : false;
	set_base(format, flags);
	return (i);
}
