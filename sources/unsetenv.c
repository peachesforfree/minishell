/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:53:06 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:53:08 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void    ft_freelst(t_list *list)
{
    if (!list)
        return;
    if (list->content)
    {
        ft_bzero(list->content, list->content_size);
        free(list->content);
    }
    ft_bzero(list, sizeof(list));
    free(list);
}

t_list  *ft_nodebefore(t_list *current, t_list *head)
{
    while (head != NULL && head->next != current)
        head = head->next;
    return (head);
}

void    remove_from_list(t_list *node, t_list **head)
{
    t_list  *temp;

    temp = *head;
    if (temp == node)
        *head = temp->next;
    else
    {
        temp = ft_nodebefore(node, temp);
        if (temp != NULL)
            temp->next = node->next;
    }
    ft_freelst(node);
}

int     ft_unsetenv(t_env *env, char **argv_ptr)
{
    int ret;
    int count;
    t_list  *list;
    int     i;

    count = 0;
    ret = 0;
    i = 1;
    (void)argv_ptr;
    while (argv_ptr[count] != NULL)
        count++;
    if (count >= 2)
    {
        while (i < count)
        {
            list = in_list(argv_ptr[i], env->environ);
            remove_from_list(list, &env->environ);
            i++;
        }
    }
    else
        printf("unsetenv: Too few arguments.");
    return (ret);
}
