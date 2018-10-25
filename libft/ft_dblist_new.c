/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblist_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:21:59 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 00:22:00 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dblist	*ft_dblist_new(void)
{
	t_dblist *temp;

	if (!(temp = (t_dblist*)malloc(sizeof(t_dblist))))
		return (NULL);
	temp->next = NULL;
	temp->last = NULL;
	temp->content = NULL;
	return ((t_dblist*)temp);
}
