/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:53:48 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:53:49 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_list        *copy_environ(char **environ)
{
    t_list      *list;
    t_list      *temp;
    int         i;
    
    i = 0;
    list = NULL;
    temp = NULL;
    while (environ[i] != NULL)
    {
        if (temp == NULL)
        {
            list = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
            temp = list;
        }
        else
        {
            temp->next = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
            temp = temp->next;
        }
        i++;
    }
    return (list);
}

void        env_init(t_env *env, char **environ)
{
    env->buffer = ft_memalloc(STDIN_BUFFER);
    env->flags = 0;
    env->buffer_size = STDIN_BUFFER;
    env->buffer_count = 0;
    env->environ = copy_environ(environ);
    env->arguments = NULL;
    env->argument_count = 0;
    env->error_message = 0;
}

void        free_command_list(t_env *env)
{
    t_list      *current;
    t_list      *last;

    current = env->arguments;
    while (current != NULL)
    {
        last = current;
        current = current->next;
        ft_bzero(last->content, last->content_size);
        free(last->content);
        ft_bzero(last, sizeof(t_list));
        free(last);
    }
}      
