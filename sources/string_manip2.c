/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manip2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:53:23 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:53:25 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"
int         char_count(char *str, char c)
{
    int     i;
    int     count;

    i = 0;
    count = 0;
    while (str[i] != '\0')
    {
        if(str[i] == c)
            count++;
        i++;
    }
    return (count);
}
