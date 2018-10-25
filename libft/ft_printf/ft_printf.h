/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:46:31 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/05 19:00:36 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>

# define MINUS				0b00000001
# define PLUS				0b00000010
# define SPACE				0b00000100
# define HASH				0b00001000
# define ZERO				0b00010000

typedef	struct		s_flags
{
	unsigned char	flag;
	int				width;
	int				precision;
	int				length;
	int				data_type;
	char			invalid_spec;
	bool			caps;
	int				written_chars;
	int				index;
	int				base;
}					t_flags;

int					ft_printf(const char *format, ...);
void				print_format_string(const char *format, t_flags *flags);
void				check_flags(const char *format, t_flags *flags);
int					check_for_doubles(const char *format, char c,
		t_flags *flags);
void				check_width_precision(const char *format, t_flags *flags);
void				check_length(const char *format, t_flags *flags);
int					check_conversion(char format, t_flags *flags);
void				parse_args(t_flags *flags, va_list *arg, int conv);
void				print_char(t_flags *flags, va_list *arg, int base);
void				print_signed(t_flags *flags, va_list *arg, int base);
void				print_unsigned(t_flags *flags, va_list *arg, int base);
void				print_string(t_flags *flags, va_list *arg, int base);
void				ft_putchar_mem(t_flags *flags, char c);
void				ft_putnbr_mem(t_flags *flags, intmax_t nbr, int base);
void				ft_putunbr_mem(t_flags *flags, uintmax_t nbr, int base);
intmax_t			typecast_num(t_flags *flags, intmax_t nbr);
uintmax_t			typecast_unum(t_flags *flags, uintmax_t nbr);
int					zeroes_signed(t_flags *flags, intmax_t nbr, int base);
int					ft_numlen_ull(uintmax_t value, unsigned int base);
int					ft_numlen_ll(intmax_t value, int base);
intmax_t			ft_power_ll(intmax_t nbr, intmax_t power);
void				print_sign(t_flags *flags, intmax_t nbr);
void				print_prefix(t_flags *flags, uintmax_t nbr);
void				ft_putchar(char c);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
uintmax_t			ft_power_ull(uintmax_t nbr, uintmax_t power);
int					zeroes_unsigned(t_flags *flags, uintmax_t nbr, int base);
int					ft_isspace(const char *s);

#endif
