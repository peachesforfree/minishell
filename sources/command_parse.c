#include "../includes/mini_shell.h"

int         read_line(t_env *env)
{
	char    *line;
 
	line = env->buffer;
	ft_bzero(env->buffer, env->buffer_size);
	env->buffer_count = 0;
	ft_putstr(COMMAND_PROMPT);
	free_command_list(env);
	while (1)
	{
		read(STDIN, &line[env->buffer_count], 1);        
		if (line[env->buffer_count] == '\n')
		{
			line[env->buffer_count] = '\0';
			return (1);
		}
		if (env->buffer_count == env->buffer_size)
		{
			env->buffer = ft_realloc(env->buffer, env->buffer_size);
			env->buffer_size += STDIN_BUFFER;
			line = env->buffer;
		}
		env->buffer_count += 1;
	}
	return (1);
}

t_list      *env_expansion(t_env *env, t_list *list)                   //List is user input tokens 
{
	t_list  *current;
	char    *string;
	char    *var;

	current = list;
	while (current != NULL)
	{
		string = current->content;
		var = ft_strchr(string, '$');
		if (var != NULL)
		{
			if (list_check(&var[1], env->environ))
			{
				var[0] = '\0';
				current->content = ft_strnjoin( current->content, list_check(&var[1], env->environ), 1);
			}
		}
/*      On second thought ... move this to the fd_cd function listing
		else if ( If only argument is "~" )
		{
			//print out old PWD
		}
		else if ( if the only argument is "-" )
		{
			//takes you to OLDPWD and prints it out
		}
		else if ( checking if CD is alone)
		{
			//put home dir into this 
		}
*/
		current = current->next;
	}
	return(list);
}

int        parse_command_line(t_env *env)
{
	int     count;
	t_list  *tokens;

	tokens = NULL;
	count = quote_count(env->buffer);
	if (count % 2 != 0 && count != 0)
	{
		env->error_message = QUOTE_WRONG;
		return(-1);
	}
	string_split_list(&tokens, env->buffer);
	tokens = env_expansion(env, tokens);
	env->arguments = tokens;
	if (env->argument_ptr != NULL)
	{
		free(env->argument_ptr);
		env->argument_ptr = NULL;
	}
	env->argument_ptr = char_ptr_from_list(env->arguments);
	if (env->environ_ptr != NULL)
	{
		free(env->environ_ptr);
		env->environ_ptr = NULL;
	}
	env->environ_ptr = char_ptr_from_list(env->environ);
	return (0);
}