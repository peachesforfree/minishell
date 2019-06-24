/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 18:53:01 by sbalcort          #+#    #+#             */
/*   Updated: 2019/06/23 18:53:02 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
**	allocates memory for new node
**	if void ptr is input, content is set to that
**	else its null
**	next is set to null
*/

t_node		*alloc_node(void *stuff)
{
	t_node *new_node;

	new_node = (t_node*)ft_memalloc(sizeof(t_node));
	new_node->content = stuff;
	new_node->next = NULL;
	return (new_node);
}
