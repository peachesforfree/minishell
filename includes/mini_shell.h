#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <fcntl.h> //open write close
# include <../libft/libft.h>

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

# define STDIN           0
# define EXECLOC         "PATH"
# define STDIN_BUFFER    4096
# define COMMAND_PROMPT  "$>"
# define EXIT_CODE       1
# define DELIMITER       " \""
# define ENVVARCHR          '$'

# define QUOTE_WRONG     1

typedef struct      s_env
{
    //for reading user input
    char        *buffer;
    int         buffer_size;
    int         buffer_count;

    //error codes and flags for exit message
    int         flags;
    int         error_message;
    
    //environment variables
    t_list      *environ;
    char        **environ_ptr;
    
    //Arguments from user and passed into programs
    t_list      *arguments;
    char        **argument_ptr;
    int         argument_count;
}                   t_env;

void    remove_from_list(t_list *node, t_list **head);
int     ft_unsetenv(t_env *env, char **argv_ptr);
void    remove_from_list(t_list *node, t_list **head);
t_list  *ft_nodebefore(t_list *current, t_list *head);
void    ft_freelst(t_list *list);
int         char_count(char *str, char c);
char        *find_path(t_env *env);
char        **assemble_env_list(char *str, char d, t_list *list);
char        **tlst_to_char_arry(t_list *list);
void        env_init(t_env *env, char **environ);
t_list        *copy_environ(char **environ);
int     ft_setenv(t_env *env, char **argv_ptr);
t_list     *in_list(char *str, t_list *list);
int     ft_strccmp(char *s1, char *s2, char c);
int         quote_count(char *buffer);
void        free_2d_arr(char **arr);
int         is_builtin(char *str);
int     ft_exit(t_env *env, char **argv_ptr);
int     ft_env(t_env *env, char **argv_ptr);
int         event_loop(t_env *env);
void    string_split_list(t_list **head, char *buffer);
char     **char_ptr_from_list(t_list *list);
int     ft_lstcount(t_list *list);
int        check_directory(DIR *directory, t_list *list);
char        *list_check(char *str, t_list *list);
t_list      *ft_lstappend(t_list *head, char *str, int i);
int         execute_command(t_env *env);
int     forkin_time(char *path, char **arguments, char **envp);
int     ft_echo(t_env *env, char **argv_ptr);
int         read_line(t_env *env);
int        parse_command_line(t_env *env);
t_list      *env_expansion(t_env *env, t_list *list);
int     ft_cd(t_env *env, char **argv_ptr);
int     directory_check(char **argv_ptr);
t_list    *pwd_swap(t_env *env);
void		deconstruct(t_env *env);
void		free_2d_char(char **str);
void		free_list(t_list *temp);


#endif