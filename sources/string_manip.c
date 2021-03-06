/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:53:35 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:53:37 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char			**tlst_to_char_arry(t_list *list)
{
	char	**temp;
	int		count;
	t_list	*current;

	count = 0;
	current = list;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	temp = (char**)ft_memalloc(sizeof(char*) * count);
	temp[count] = NULL;
	current = list;
	count = 0;
	while (temp != NULL)
	{
		temp[count] = current->content;
		count++;
		current = current->next;
	}
	return (temp);
}

char			**assemble_env_list(char *str, char d, t_list *list)	//shorten by 6 lines
{
	char		**result;
	char		*temp;
	int			temp_len;
	int			word_count;
	int			i;

	i = 0;
	result = NULL;
	while (list != NULL)
	{
		if (ft_strcmp(list->content, str) == '=')
		{
			temp_len = 0;
			temp = ft_strchr(list->content, '=') + 1;
			if (char_count(temp, d) == 0)
				return (NULL);
			word_count = char_count(temp, d);
			result = (char**)ft_memalloc(sizeof(char*) * (word_count + 1));
			while (temp[0] != '\0' && i < word_count)
			{
				temp_len = ft_strchr(temp, d) - temp;
				result[i] = ft_strnew(temp_len);
				ft_strncpy(result[i], temp, temp_len);
				temp += temp_len + 1;
				i++;
			}
			return (result);
		}
		list = list->next;
	}
	return (result);
}

void			find_path_misc(char **path_list, DIR *directory)
{

	free_2d_char(path_list);
	(void)directory;
	// closedir(directory);
}

char			*find_path(t_env *env)
{
	char	**path_list;
	DIR		*directory;
	char	*abs_path;
	t_list	*temp;
	int		i;

	i = 0;
	temp = NULL;
	path_list = assemble_env_list("PATH", ':', env->environ);
	while (path_list[i] != NULL)
	{
		directory = opendir(path_list[i]);
		if (check_directory(directory, env->arguments))
		{
			temp = env->arguments;
			abs_path = ft_strjoin(path_list[i], "/");
			abs_path = ft_strnjoin(abs_path, temp->content, 1);
			find_path_misc(path_list, directory);
			closedir(directory);
			return (abs_path);
		}
		closedir(directory);
		i++;
	}
	find_path_misc(path_list, directory);
	return (NULL);
}