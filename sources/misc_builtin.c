/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:54:41 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:54:42 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int     ft_env(t_env *env, char **argv_ptr)
{
    int         ret;
    t_list      *list;

    ret = 0;
    (void)argv_ptr;
    list = env->environ;
    while (list != NULL)
    {
        printf("%s\n",list->content);
        list = list->next;
    }
    return (ret);
}

int     ft_exit(t_env *env, char **argv_ptr)
{
    int ret;

    ret = -1;
    (void)argv_ptr;
    (void)env;
    return (ret);
}

char *g_builtin[] = { NULL, "echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};

int         is_builtin(char *str)
{
    int     i;

    i = 1;
    while (g_builtin[i] != NULL)
    {
        //printf("Compare: %s\t%s\n", str, g_builtin[i]);
        if (ft_strstr(str, g_builtin[i]) != NULL && (ft_strlen(str) == ft_strlen(g_builtin[i])))
            return (i);
        i++;
    }
    return (0);
}
