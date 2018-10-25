/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblist_bridge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:24:12 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 00:24:13 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblist_bridge(t_dblist *first, t_dblist *second)
{
	if (!first || !second)
		return ;
	first->next = second;
	second->last = first;
}
