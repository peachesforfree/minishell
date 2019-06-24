/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:55:30 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:55:31 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void		free_list(t_list *temp)
{
	t_list		*current;
	t_list		*last;

	current = temp;
	last = current;
	current = current->next;
	while (last != NULL)
	{
		ft_bzero(last->content, ft_strlen(last->content));
		free(last->content);
		last->content_size = 0;
		last->content = NULL;
		last->next = NULL;
		free(last);
		last = current;
		if (current)
			current = current->next;
	}
}

void		deconstruct(t_env *env)
{
	void	*temp;

	temp = env->buffer;
	ft_bzero(temp, env->buffer_size);
	free(temp);
	env->buffer = NULL;
	free_list(env->environ);
	//clear and free environ_ptr ?
	free_list(env->arguments);
	//free and clear argument_ptr ?
	ft_bzero(env, sizeof(env));
}

void		free_2d_char(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		ft_bzero(str[i], ft_strlen(str[i]));
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}