/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:56:39 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:56:41 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_list    *pwd_swap(t_env *env)
{
	t_list      *pwd;
	t_list      *old_pwd;
	char        *temp;

	pwd = in_list("PWD", env->environ);
	old_pwd = in_list("OLDPWD", env->environ);
	temp = ft_strchr(old_pwd->content, '=');
	temp[1] = '\0';
	old_pwd->content = ft_strnjoin(old_pwd->content, (ft_strchr(pwd->content, '=') + 1), 1);
	temp = ft_strchr(pwd->content,'=');
	temp[1] = '\0';
	pwd->content_size = ft_strlen(pwd->content);
	return (pwd);
}

int     directory_check(char **argv_ptr)
{
	char    *temp;
	int     i;

	i = 1;
	temp = ft_strnjoin(getcwd(NULL, 0), "/", 1);
	temp = ft_strnjoin(temp, argv_ptr[1], 1); 
	if (access(temp, R_OK | X_OK) != 0)
	{
		i = 0;
	}
	ft_bzero(temp, ft_strlen(temp));
	free(temp);
	if (i == 0)
		printf("cd: no such file of directory: %s", argv_ptr[1]);
	return(i);    
}

int     ft_cd(t_env *env, char **argv_ptr)
{
	int     ret;
	int     i;
	char    *temp;
	t_list  *list;

	ret = 0;
	i = 0;
	temp = NULL;
	list = NULL;
	while (argv_ptr[i] != NULL)
		i++;
	if (i == 2 && directory_check(argv_ptr))
	{
		//make if condition for '~' use environtment variable expansion for HOMEDIR
		chdir(argv_ptr[1]);
		temp = getcwd(NULL, 0);
		list = pwd_swap(env);
		list->content = ft_strnjoin(list->content, "/", 1);
		list->content = ft_strnjoin( list->content, temp, 3);
		ft_bzero(temp, ft_strlen(temp));
		free(temp);
	}
	else if (i == 1)
	{
		//return to old pwd
	}
	else if (i > 2)
		printf("cd: Too many arguments\n");    
	return (ret);
}
