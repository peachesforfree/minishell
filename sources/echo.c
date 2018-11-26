/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:56:12 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:56:13 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
int     ft_echo(t_env *env, char **argv_ptr)
{
    int     ret;
    int     i;

    i = 1;
    (void)env;
    ret = 0;
    if (argv_ptr[i] != NULL)
    {
        while (argv_ptr[i] != NULL)
        {
            printf("%s", argv_ptr[i]);
            if (argv_ptr[i + 1] != NULL)
                printf(" ");
            i++;
        }
        printf("\n");
    }
    return (ret);
}
