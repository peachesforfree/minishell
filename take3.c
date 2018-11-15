#include "includes/mini_shell.h"
#include <stdio.h>
#include <fcntl.h> //open write close

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
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

int     ft_lstcount(t_list *list)
{
    int i;

    i = 0;
    while (list != NULL)
    {
        i++;
        list = list->next;
    }
    return (i);
}

char     **char_ptr_from_list(t_list  *list)
{
    char    **current_ptr;
    int     i;

    current_ptr = (char **)ft_memalloc(sizeof(char*) * (ft_lstcount(list) + 1));
    i = 0;
    while (list != NULL)
    {
        current_ptr[i] = list->content;
        i++;
        list = list->next;
    }
    current_ptr[i] = NULL;
    return (current_ptr);
}

char        *list_check(char *str, t_list *list)
{
    char    *ret;

    ret = NULL;
    while (list != NULL)
    {
        if (ft_strcmp(str, list->content))
        {
            return (ft_strchr(list->content, '=') + 1);
        }
        list = list->next;
    }
    return (ret);
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

char        **tlst_to_char_arry(t_list *list)
{
    char    **temp;
    int     count;
    t_list  *current;

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

int        check_directory(DIR *directory, t_list *list)
{
    char            *str;
    struct dirent   *file;

    str = list->content;
    while ((file = readdir(directory)) != NULL)
    {
        if (ft_strstr(file->d_name, str) && ft_strlen(str) == ft_strlen(file->d_name))
            return (1);
    }
    return (0);
}

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

char        **assemble_env_list(char *str, char d, t_list *list)
{
    char    **result;
    char    *temp;
    int     temp_len;
    int     word_count;
    int     i;

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
            while(temp[0] != '\0' && i < word_count)
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

char        *find_path(t_env *env)  //here need to find if the first argument is an alias for what is in the paths
{
    char            **path_list;
    DIR             *directory;
    char            *abs_path;
    t_list          *temp;
    int             i;

    i = 0;
    abs_path = NULL;
    path_list = assemble_env_list("PATH", ':', env->environ);
    while (path_list[i] != NULL)
    {
        directory = opendir(path_list[i]);
        if (check_directory(directory, env->arguments))
        {
            temp = env->arguments;
            abs_path = ft_strjoin(path_list[i], "/");
            abs_path = ft_strnjoin(abs_path, temp->content, 1);
            //produce complete path with executable at end
            //free path_list at end
            return(abs_path);
        }
        closedir(directory);
        i++;
    }                                                               
    return (NULL);
}

int     ft_echo(t_env *env, char **argv_ptr)
{
    int     ret;
    int     i;

    i = 1;
    (void)env;
    ret = 0;
    if (argv_ptr[i] != NULL)
    {
        while (argv_ptr[i] != NULL)
        {
            printf("%s", argv_ptr[i]);
            if (argv_ptr[i + 1] != NULL)
                printf(" ");
            i++;
        }
        printf("\n");
    }
    return (ret);
}

void    pwd_swap(t_env *env)            ///////////////////// write a function that will put PWD into PWD       ...     and maybe include putting argv_ptr into PWD
{
    list = in_list("PWD", env->environ);
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
    if (i == 2)
    {
        //make if condition for '~' use environtment variable expansion for HOMEDIR
        chdir(argv_ptr[1]);
        temp = getcwd(NULL, 0);
        pwd_swap(env);
        //put temp in PWD environ
    }
    if (i == 1)
    {
        //return to old pwd
    }
    if (i > 2)
        printf("cd: Too many arguments\n");    
    return (ret);
}

/*
** int  ft_strccmp(char *s1, char *s2, char c)
**will compare each char in the string until either differes
**only when the s2 is qual to special char AND s1 is '\0' meaning both strings compare upto the special char
*/

int     ft_strccmp(char *s1, char *s2, char c)
{
    int     i;

    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            break;
        i++;
    }
    if (s2[i] == c && s1[i] == '\0')
            return (1);
    return (0);
}

t_list     *in_list(char *str, t_list *list)
{
    while (list != NULL)
    {
        if (ft_strccmp(str, list->content, '='))
            return (list);
        list = list->next;
    }
    // search through the program and look if i have already made something like this. (i think i have)
    return (NULL);
}

int     ft_setenv(t_env *env, char **argv_ptr)
{
    int     ret;
    int     argc;
    char    *temp;
    t_list  *list;

    argc = 0;
    (void)env;
    while (argv_ptr[argc] != NULL)
        argc++;
    ret = 0;
    list = in_list(argv_ptr[1], env->environ);
    if ((argc == 3 || argc == 2) && list == NULL)
    {
        temp = ft_strdup(argv_ptr[1]);
        temp = ft_strnjoin( temp, "=",1);
        if (argc == 3)
            temp = ft_strnjoin(temp, argv_ptr[2], 1);
        ft_lstappend(env->environ, temp, ft_strlen(temp));
        free(temp);
    }
    else if (list != NULL)
    {
        temp = ft_strchr(list->content, '=') + 1;
        temp[0] = '\0';
        if (argc == 3) //change whats in there
            list->content = ft_strnjoin(list->content, argv_ptr[2], 1);
    }
    else
    {
        printf("usage: setenv [variable name] [variable value]");
    }
    return (ret);
}

void    ft_freelst(t_list *list)
{
    if (!list)
        return;
    if (list->content)
    {
        ft_bzero(list->content, list->content_size);
        free(list->content);
    }
    ft_bzero(list, sizeof(list));
    free(list);
}

t_list  *ft_nodebefore(t_list *current, t_list *head)
{
    while (head != NULL && head->next != current)
        head = head->next;
    return (head);
}

void    remove_from_list(t_list *node, t_list **head)
{
    t_list  *temp;

    temp = *head;
    if (temp == node)
        *head = temp->next;
    else
    {
        temp = ft_nodebefore(node, temp);
        if (temp != NULL)
            temp->next = node->next;
    }
    ft_freelst(node);
}

int     ft_unsetenv(t_env *env, char **argv_ptr)
{
    int ret;
    int count;
    t_list  *list;
    int     i;

    count = 0;
    ret = 0;
    i = 1;
    (void)argv_ptr;
    while (argv_ptr[count] != NULL)
        count++;
    if (count >= 2)
    {
        while (i < count)
        {
            list = in_list(argv_ptr[i], env->environ);
            remove_from_list(list, &env->environ);
            i++;
        }
    }
    else
        printf("unsetenv: Too few arguments.");
    return (ret);
}

int     ft_env(t_env *env, char **argv_ptr)
{
    int         ret;
    t_list      *list;

    ret = 0;
    (void)argv_ptr;
    list = env->environ;
    while (list != NULL)
    {
        printf("%s\n",list->content);
        list = list->next;
    }
    return (ret);
}

int     ft_exit(t_env *env, char **argv_ptr)
{
    int ret;

    ret = -1;
    (void)argv_ptr;
    (void)env;
    return (ret);
}

char *g_builtin[] = { NULL, "echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};

int		(*g_func[]) (t_env *env, char **user_input) = { NULL, ft_echo, ft_cd, ft_setenv, ft_unsetenv, ft_env, ft_exit};

int         is_builtin(char *str)
{
    int     i;

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

int         execute_command(t_env *env)
{
    int     ret;
    char    *path;
    char    **argv_ptr;
    //t_list  *temp;

    ret = 0;
    argv_ptr = env->argument_ptr;
    if (argv_ptr[0] != NULL && is_builtin(argv_ptr[0]))
        ret = (g_func[is_builtin(argv_ptr[0])])(env, argv_ptr);
    else if (argv_ptr[0] != NULL) //maybe change to list count more than 1
    {
        if ((access(argv_ptr[0], X_OK) == 0))
        {
            forkin_time(argv_ptr[0], argv_ptr, env->environ_ptr);
        }
        path = find_path(env);
        if ((access(path, X_OK) == 0))
            forkin_time(path, env->argument_ptr, env->environ_ptr);
        free(path);
    }
    else
        printf("Error path not found\n");
    //free path, arguments, envp
    return (ret);
}

int         event_loop(t_env *env)
{
    int     ret;

    ret = 0;
    while (ret == 0 && read_line(env))
    {
        if (parse_command_line(env) < 0)
            printf("Error message\n");//make some error message

                                                                                                                // t_list  *fakeshit;
                                                                                                                // fakeshit = env->arguments;
                                                                                                                // while (fakeshit != NULL)
                                                                                                                // {
                                                                                                                //     printf("'%s'\n", fakeshit->content);
                                                                                                                //     fakeshit = fakeshit->next;
                                                                                                                // }
    ret = execute_command(env);
    }
    return (0);
}   //if return -1. something wrong ... if return >= 0 all is good

int         main(int argc, char **argv, char **environ)
{
    t_env   env;
    (void)argc;
    (void)argv;

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
 *              staret line 502
 * 
 * 
 * **********************/
