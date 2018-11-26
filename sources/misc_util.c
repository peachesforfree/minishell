/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:54:18 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:54:20 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void        free_2d_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
    {
        ft_bzero(arr[i], ft_strlen(arr[i]));
        free(arr[i]);
        i++;
    }
    free(&arr);
}

int         quote_count(char *buffer)
{
    int     count;
    int     i;

    i = 0;
    count = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == '"')
            count++;
        i++;
    }
    return (count);
}
