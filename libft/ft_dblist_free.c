/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblist_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 00:22:58 by sbalcort          #+#    #+#             */
/*   Updated: 2018/07/10 00:23:00 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dblist_free(t_dblist *list)
{
	if (list == NULL)
		return ;
	if (list->content != NULL)
		free(list->content);
	free(list);
}
