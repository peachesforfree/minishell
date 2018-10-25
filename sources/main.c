#include "../includes/mini_shell.h"
#include <stdio.h>
#include <fcntl.h> //open write close

#define STDIN           0
#define EXECLOC         "PATH"
#define STDIN_BUFFER    4096
#define COMMAND_PROMPT  "$>"
#define EXIT_CODE       1


int         error_handle(char *str, int in)
{
    printf("%s\n", str);
    return (in);
}

typedef struct      s_env
{
    char        *buffer;
    int         flag;
    int         buffer_size;
    int         buffer_count;
    t_list      *environ;
//    t_list      *path;
    char        **command_list;
}                   t_env;


int     ft_echo(t_env *env, char **user_input)
{
    int i;

    i = 1;
    while (user_input[i] != NULL)
    {
        ft_putstr(user_input[i]);
        ft_putchar(' ');
        i++;
    }
    ft_putchar('\n');
    return (i);
}

int     ft_cd(t_env *env, char **user_input)
{
    int i;

    i = 1;
    printf("you entered CD\n");
    return (i);
}

int     string_count(char **str)
{
    int i;

    i = 1;
    while (str[i] != NULL)
        i++;
    return (i);
}

t_list    *search_for_variable(t_env *env, char *in)
{
    t_list  *temp;
    char    *str;

    temp = env->environ;
    while (temp != NULL)
    {
        str = temp->content;
        if (ft_strstr(str, in) && ((int)ft_strlen(in) == (int)(ft_strchr(str, '=') - str)))
            return (temp);
        temp = temp->next;
    }
    return (temp);
}

int     ft_env(t_env *env, char **user_input)
{
    int     ret;
    t_list  *environ;

    environ = env->environ;
    ret = 1;
    while (environ != NULL)
    {
        printf("%s\n", environ->content);
        environ = environ->next;
    }
    return (ret);
}

t_list    *append_list(t_env *env, char *string)
{
    t_list  *list;
    char    *str;

    list = env->environ;
    if (list == NULL)
    {
        env->environ = ft_lstnew(string, ft_strlen(string));
        env->environ->content = ft_strnjoin(env->environ->content, "=", 1);
        return (env->environ);
    }
    else if (list != NULL)
    {
        list = env->environ;
        while (list->next != NULL)
            list = list->next;
        list->next = ft_lstnew(string, ft_strlen(string));
        list->next->content = ft_strnjoin(list->next->content, "=", 1);
    }
    return (list->next);
}


int     ft_setenv(t_env *env, char **user_input)
{
    int     ret;
    int     i;
    t_list  *found;

    i = 1;
    ret = 1;

    if (user_input[i] == NULL)                      //if no user input, print out env
        return (ft_env(env, user_input));
    if (string_count(user_input) > 3)
        return (error_handle("setenv: too many arguments", -1));
        found = search_for_variable(env, user_input[1]); //variable name
        if (found != NULL)
            ft_bzero(ft_strchr(found->content, '=') + 1, 1);
        else
            found = append_list(env, user_input[1]);
        if (found != NULL && user_input[2] != NULL)
            found->content = ft_strnjoin(found->content, user_input[2], 1);
    return (ret);
}

void    remove_link(t_env *env, t_list *node)
{
    t_list *current;

    current = env->environ;
    if (current == NULL)
        return ;
    if (env->environ == node)
    {
        free(node->content);
        free(node);
        env->environ = NULL;
        return ;
    }
    while (current->next != NULL)
    {
        printf("\t\t\tcurrent->content: %s\n", current->content);
        if (current->next == node)
        {
            current->next = current->next->next;
            free(node->content);
            free(node);
        }
        if (current->next != NULL)
        current = current->next;
    }
}

int     ft_unsetenv(t_env *env, char **user_input)
{
    int     i; 
    t_list  *found;

    i = 1;
    if (user_input[i] == NULL)
        return(error_handle("unsetenv: Too few arguments.", -1));
    while (user_input[i] != NULL)
    {
        found = search_for_variable(env, user_input[i]);
        if (found != NULL)
            remove_link(env, found);
        i++;
    }

    return (i);
}

int     ft_exit(t_env *env, char **user_input)
{
    env->flag = EXIT_CODE;
    return (1);
}

char *g_builtin[] = { NULL, "echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};

int		(*g_func[]) (t_env *env, char **user_input) = { NULL, ft_echo, ft_cd, ft_setenv, ft_unsetenv, ft_env, ft_exit};



t_list      *deep_copy(char **environ)
{
    t_list  *head;
    t_list  *current;
    int     i;
    char    *str;

    i = 0;
    head = NULL;
    while (environ[i] != NULL)
    {
        if (head == NULL)
        {
            head = ft_lstnew(environ[i],ft_strlen(environ[i]) + 1);
            current = head;
        }
        else
        {
            current->next = ft_lstnew(environ[i],ft_strlen(environ[i]) + 1);
            current = current->next;
        }
        i++;
    }
    return (head);
}

void            free_strings(char **strings)
{
    int i;

    i = 0;
    while (strings[i] != NULL)
    {
        free(strings[i]);
        i++;
    }
    free(strings);
}

t_list        *if_path(t_list *env)
{
    t_list      *temp;
    char        **strings;

    temp = NULL;
    if (env != NULL)
    {
        temp = env;
        while (env != NULL)
        {
            if (ft_strcmp( env->content, EXECLOC) == '=')
            {
                strings = ft_strsplit(ft_strchr(env->content, '=') + 1, ':');
                temp = deep_copy(strings);
                free_strings(strings);
                return (temp);
            }
            env = env->next;
        }
    }
    return (temp);
}

void        free_list(t_list *list)
{
    t_list      *temp;

    while (list != NULL)
    {
        temp = list->next;
        free(list->content);
        free(list);
        list = temp;
    }
}

void        close_up(t_env *env)
{
    free_list(env->environ);
    env->environ = NULL;
    //free_list(env->path);
    //env->path = NULL;
}

void        clear_buffer(t_env *env)
{
    if (env->buffer_count > 0)
    {
        ft_bzero(env->buffer, env->buffer_count);
        env->buffer_count = 0;
    }
}

int         read_line(t_env *env)
{
    char    *line;
 
    line = env->buffer;
    clear_buffer(env);
    ft_putstr(COMMAND_PROMPT);
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
}

int         is_builtin(char *str)
{
    int     i;
    char    *found;

    i = 1;
    while (g_builtin[i] != NULL)
    {
        //printf("Compare: %s\t%s\n", str, g_builtin[i]);
        if (ft_strstr(str, g_builtin[i]) != NULL && (ft_strlen(str) == ft_strlen(g_builtin[i])))
            return (i);
        i++;
    }
    return (0);
}

int        execute_command(t_env *env, char **command)
{
    int     ret;

    ret = 0;
    if (command[0] != NULL && is_builtin(command[0]))
        ret = (g_func[is_builtin(command[0])])(env, command);
    else if (command[0] != NULL)
    {
    //find is command is in path
    //fork command
    //wait on fork
    //each will return 1 upon use. 
    //if nothing is found, an error message needs to be printed in previous 'shell_loop' function
    }
    return (ret);
}

int         shell_loop(t_env *env)
{
    int     ret;

    ret = 0;
    while ((env->flag != EXIT_CODE) && read_line(env))
    {
        env->command_list = parse(env->buffer);



        //ret = execute_command(env, env->command_list);
        //here do a check to make sure anything program was ran
        free_strings(env->command_list);
    }
    return (ret);
}

int main(int argc, char **argv, char **environ)
{
    t_env   env;
    int     ret;

    ret = 0;
    env.environ = deep_copy(environ);
//    env.path = if_path(env.environ);
    env.buffer = ft_strnew(STDIN_BUFFER);
    env.buffer_count = 0;
    env.buffer_size = STDIN_BUFFER;
    env.flag = 0;


    ret = shell_loop(&env);
    /*t_list *list = env.path;
    while (list != NULL)
    {
        printf("%s\n",list->content);
        list = list->next;
    }

    close_up(&env);
    while (1)
    {
    }*/
    return (ret);
}

//      gcc sources/main.c includes/mini_shell.h libft/libft.a
/***********************************                    DO TO LIST

when looking at the ' and "
    need to see when allowed to replace escaped chars
    when to replace $PARAM
    when to remove WHITESPACE
    when to remove '
    when to remove "

 
Parse is now working properly .... (still need to include the use of parsing out the $ symbol and all non delimiting symbols)
now need to cover parameter expansion

cd

searching through PATH with executable names



TESTS

$> foo
$> /bin/ls -laf
$> /bin/ls -l -a -f

BUILTINS

$> exit
$> echo "It works"
$> echo It work

$> cd /absolute/path/of/your/choice
$> /bin/pwd
$> cd relative/path/of/your/choice
$> cd

$> cd -             //needs to be the relitive path selected before
$> cd ~/path/of/your/choice






***************************************/