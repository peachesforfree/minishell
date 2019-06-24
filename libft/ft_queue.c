/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 18:43:40 by sbalcort          #+#    #+#             */
/*   Updated: 2019/06/23 18:46:10 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
**Return 1 if the queue is empty, 0 otherwise.
*/

int			isempty(t_queue *queue)
{
	if (queue->first != NULL)
		return (0);
	return (1);
}

/*
**The first and last pointers are set to NULL.
*/

t_queue		*init(void)
{
	t_queue		*new_queue;

	new_queue = (t_queue*)ft_memalloc(sizeof(t_queue));
	new_queue->first = NULL;
	new_queue->last = NULL;
	return (new_queue);
}

/*
**Add an item to the end of the queue.
*/

void		enqueue(t_queue *queue, void *content)
{
	t_node		*new_node;

	new_node = alloc_node(content);
	if (isempty(queue))
	{
		queue->first = new_node;
		queue->last = new_node;
		return ;
	}
	queue->last->next = new_node;
	queue->last = new_node;
	return ;
}

/*
**Remove the first item from the queue and return it.
**If the queue is empty, the function returns NULL.
*/

void		*dequeue(t_queue *queue)
{
	t_node		*current;
	void		*ret;

	if (isempty(queue))
		return (NULL);
	current = queue->first;
	ret = current->content;
	queue->first = queue->first->next;
	free(current);
	return (ret);
}

/*
**Return the first item of the queue.
**If the queue is empty, the function returns NULL.
*/

void		*peek(t_queue *queue)
{
	t_node		*current;
	void		*ret;

	if (isempty(queue))
		return (NULL);
	current = queue->first;
	ret = current->content;
	return (ret);
}
