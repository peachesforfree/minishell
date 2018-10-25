/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fronttrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:21:08 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 00:21:09 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_frontstrim(char *string)
{
	int	i;

	i = 0;
	while (ft_isspace(&string[i]) && string[i] != '\0')
		i++;
	return (&string[i]);
}
