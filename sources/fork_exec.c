/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:55:38 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:55:40 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int     forkin_time(char *path, char **arguments, char **envp)
{
	//need to create absolute path of executable
	//need to generate a char** pointer to the argv
	int         status;
	pid_t       pid;

	status = 1;
	pid = fork ();
	if (pid == 0)       /* This is the child process.  Execute the shell command. */
	{
		execve(path, arguments, envp);
		// if (execve(path, arguments, envp) < 0)
		//     printf("ERRNO MSG: %s\n", strerror(errno));
		//execl (SHELL, SHELL, "-c", command, NULL);
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)   /* The fork failed.  Report failure.  */
	{
		status = -1;
		printf("Error\n");
	}
	else                /* This is the parent process.  Wait for the child to complete.  */
	{
		if (waitpid (pid, &status, 0) != pid)
		{
			status = -1;
		}
	}
	return (status);
}

int		(*g_func[]) (t_env *env, char **user_input) = { NULL, ft_echo, ft_cd, ft_setenv, ft_unsetenv, ft_env, ft_exit};

int         execute_command(t_env *env)
{
	int     ret;
	char    *path;
	char    **argv_ptr;
	//t_list  *temp;

	ret = 0;
	path = NULL;
	argv_ptr = env->argument_ptr;
	if (argv_ptr[0] != NULL && is_builtin(argv_ptr[0]))
		ret = (g_func[is_builtin(argv_ptr[0])])(env, argv_ptr);
	else if (argv_ptr[0] != NULL) //maybe change to list count more than 1
	{
		if ((access(argv_ptr[0], X_OK) == 0))	//checking if the executable is local
		{
			forkin_time(argv_ptr[0], argv_ptr, env->environ_ptr);
		}
		path = find_path(env);
		if ((access(path, X_OK) == 0))			//checks if the executable is in path
			forkin_time(path, env->argument_ptr, env->environ_ptr);
 		free(path);
		path = NULL;
	}
	else
		printf("Error path not found\n");
	//free path, arguments, envp
	return (ret);
}
