/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <sbalcort@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:54:55 by sbalcort          #+#    #+#             */
/*   Updated: 2018/11/26 13:54:56 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

/*
**if return -1. something wrong ... if return >= 0 all is good
*/

int			event_loop(t_env *env)
{
	int		ret;

	ret = 0;
	while (ret == 0 && read_line(env))
	{
		if (parse_command_line(env) < 0)
			printf("Error message\n");
		ret = execute_command(env);
		if (ret == -2)
		{
			if (env->argument_ptr[0] != NULL)
				printf("command not found: %s\n", env->argument_ptr[0]);
			ret = 0;
		}
		//exit returns -1 ... maybe make an exit() function for that specific command?
		if (ret == -1)
			ret = 0;
	}
	return (0);
}

int			main(int argc, char **argv, char **environ)
{
	t_env	env;
	int		ret;

	(void)argc;
	(void)argv;
	ret = 0;
	env_init(&env, environ);
	if (event_loop(&env) < 0)
		ret = -1;
	deconstruct(&env);
	return (ret);
}

/****************
 *                      gcc take3.c -g includes/mini_shell.h libft/libft.a
 *              fix the ENV espansion (only chooses the first item in the list)     Read notes command+parse.c Line 51
 *              free everything ... DONE!
 *              Make file ... check other make files how to pre or post pend ... need to prepend the sources directory
 * **********************/
