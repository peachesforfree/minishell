#include "includes/mini_shell.h"
#include <stdio.h>
#include <fcntl.h> //open write close

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




#define STDIN           0
#define EXECLOC         "PATH"
#define STDIN_BUFFER    4096
#define COMMAND_PROMPT  "$>"
#define EXIT_CODE       1
#define DELIMITER       " \""
#define ENVVARCHR          '$'

#define QUOTE_WRONG     1


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

t_list        *copy_environ(char **environ)
{
    t_list      *list;
    t_list      *temp;
    int         i;
    
    i = 0;
    list = NULL;
    temp = NULL;
    while (environ[i] != NULL)
    {
        if (temp == NULL)
        {
            list = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
            temp = list;
        }
        else
        {
            temp->next = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
            temp = temp->next;
        }
        i++;
    }
    return (list);
}

void        env_init(t_env *env, char **environ)
{
    env->buffer = ft_memalloc(STDIN_BUFFER);
    env->flags = 0;
    env->buffer_size = STDIN_BUFFER;
    env->buffer_count = 0;
    env->environ = copy_environ(environ);
    env->arguments = NULL;
    env->argument_count = 0;
    env->error_message = 0;
}

void        free_command_list(t_env *env)
{
    t_list      *current;
    t_list      *last;

    current = env->arguments;
    while (current != NULL)
    {
        last = current;
        current = current->next;
        ft_bzero(last->content, last->content_size);
        free(last->content);
        ft_bzero(last, sizeof(t_list));
        free(last);
    }
}       

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

t_list      *ft_lstappend(t_list *head, char *str, int i)
{
    t_list  *temp;
    char    *nl;

    if (str == NULL)
        return (NULL);
    if (head == NULL)
    {
        temp = ft_lstnew(str, i + 1);
        nl = temp->content;
        nl[i] = '\0';
        return (temp);
    }
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = ft_lstnew(str, i + 1);
    nl = temp->next->content;
    nl[i] = '\0';
    return (head); 
}


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
            while (!ft_isspace(&buffer[i + off]) && buffer[i + off] != '"')
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
//    tokens = env_expansion(tokens);
    env->arguments = tokens;
    return (0);
} 

int     put_test(t_env *env, char *str)
{
    ft_strcpy(env->buffer, str);
    return (1);
}

int     forkin_time(char *path, char **arguments, char **envp)
{
    //need to create absolute path of executable
    //need to generate a char** pointer to the argv
    int         status;
    pid_t       pid;

    pid = fork ();
    if (pid == 0)       /* This is the child process.  Execute the shell command. */
    {
        execve();
        //execl (SHELL, SHELL, "-c", command, NULL);
        exit (EXIT_FAILURE);
    }
    else if (pid < 0)   /* The fork failed.  Report failure.  */
        status = -1;
    else                /* This is the parent process.  Wait for the child to complete.  */
        if (waitpid (pid, &status, 0) != pid)
            status = -1;
    return (status);
}

char        **tlst_to_char_arry(t_list *list)
{
    char    **temp;
    int     count;
    t_list  *current;

    count = 0;
    current = list;
    while (temp != NULL)
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

char        *find_in_path(t_list *list, char **args)
{
    char    *path;

    //here given a list of paths
    //search each one (using opendir, readdir, closedir) if they compare with the executable in args[0]
    //if a match is found
        //make the proper exec path and return it
    return (path);
}

char        find_path(t_env *env)
{
    char    *result;
    t_list  *path_list;

    path_list = NULL;
    result = NULL;
    path_list = ft_strsplit( ft_strchr(/*find PATH in list and return content*/,  "="), ':');
    if (path_list)
    {
        result = find_in_path(path_list, env->argument_ptr);
    //first check if it is a path to a file (allocate memory for the string)
    //this is to look through all of the items in path and compare with the first one in t_list *arguments
    //if its in a path variable. then compose the absolute path (allocate memory)
    }
    return (result);
}
int         execute_command(t_env *env)
{
    int     ret;
    char    *path;
    t_list  *temp;

    ret = 0;
    // if (argv_ptr[0] != NULL && is_builtin(argv_ptr[0]))
    // {
    //     ret = (g_func[is_builtin(argv_ptr[0])])(env, argv_ptr);
    // }
    // else if (argv_ptr[0] != NULL)
    // {
        temp = env->arguments;
        path = find_path(env);
        env->arguments_ptr = tlst_to_char_arry(env->arguments);
    
        forkin_time(path, env->arguments_ptr, env->environ)
        //free(arguments);

    // }
    //free path, arguments, envp
    return (ret);
}

int         event_loop(t_env *env)
{
    int     ret;

    ret = 0;
    //while (put_test(env, "hello \"brave new\" world"))
    while (ret == 0 && read_line(env))
    {
        if (parse_command_line(env) < 0)
            printf("Error message\n");//make some error message


                                                                                                                t_list  *fakeshit;
                                                                                                                fakeshit = env->arguments;
                                                                                                                while (fakeshit != NULL)
                                                                                                                {
                                                                                                                    printf("'%s'\n", fakeshit->content);
                                                                                                                    fakeshit = fakeshit->next;
                                                                                                                }
    ret = execute_command(env);
    }
    return (0);
}   //if return -1. something wrong ... if return >= 0 all is good

int         main(int argc, char **argv, char **environ)
{
    t_env   env;

    env_init(&env, environ);
    if (event_loop(&env) < 0)
    {
        //deconstruct();
        return (-1);
    }
    //deconstruct()
    return (0);
}


/****************
 *                      gcc take3.c -g includes/mini_shell.h libft/libft.a
 * 
 *                   
 *                  
 *                              LINE 292
 * 
 * 
 * 
 * **********************/