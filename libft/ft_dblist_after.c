/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblist_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:24:53 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 00:24:54 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*double_insert_after(t_dblist *current)
{
	if (current == NULL)
		return (NULL);
	current->next = ft_dblist_new();
	current->next->last = current;
	return (current->next);
}
