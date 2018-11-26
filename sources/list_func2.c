/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:55:04 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:55:06 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void    string_split_list(t_list **head, char *buffer)
{
    int     i;
    int     off;

    i = 0;
    while (buffer[i] != '\0')
    {
        off = 0;
        if (!ft_isspace(&buffer[i]) && buffer[i] != '"')
        {
            while (buffer[i + off] != '\0' && !ft_isspace(&buffer[i + off]) && buffer[i + off] != '"')
                off++;
            *head = ft_lstappend(*head, &buffer[i], off);
            i += off;    
            continue;
        }
        else if (buffer[i] == '"')                                                                      
        {
        //    *head = ft_lstappend(*head, &buffer[i], off);
        //    off++;
            i++;
        //    i += off;
        //    off = 0;
            while (buffer[i + off] != '"' && buffer[i + off] != '\0')
                off++;
            *head = ft_lstappend(*head, &buffer[i], off);
            off++;
            i += off;
        }
        while (buffer[i] != '\0' && ft_isspace(&buffer[i]))
            i++;
    }
}
