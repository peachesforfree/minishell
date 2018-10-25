#include "includes/mini_shell.h"
#include <stdio.h>
#include <fcntl.h> //open write close



#define STDIN           0
#define EXECLOC         "PATH"
#define STDIN_BUFFER    4096
#define COMMAND_PROMPT  "$>"
#define EXIT_CODE       1
#define DELIMITER       " \""
#define ENVVARCHR          '$'


typedef struct      s_env
{
    char        *buffer;
    int         flag;
    int         buffer_size;
    int         buffer_count;
    t_list      *environ;
    t_list      *command_list;
    char        **argv_ptr;
}                   t_env;

void        free_command_list(t_env *env);
int         ft_env(t_env *env, char **argv_ptr);



void        input_var_value(t_list *list, char *var)
{
    char    *str_tmp;

    str_tmp = ft_strchr(var, '=') + 1;
    list->next = ft_lstnew(str_tmp, ft_strlen(str_tmp));
}

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
            head = ft_lstnew(NULL, 0);
            head->content = ft_lstnew(environ[i], (ft_strchr(environ[i], '=') - environ[i])); //name of variable
            input_var_value(head->content, environ[i]);
            current = head;
        }
        else
        {
            current->next = ft_lstnew(NULL, 0);
            current = current->next;
            current->content = ft_lstnew(environ[i], (ft_strchr(environ[i], '=') - environ[i])); //name of variable
            input_var_value(current->content, environ[i]);  
        }
        i++;
    }
    return (head);
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
    free_command_list(env);
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
    return (1);
}

void        append_list(t_env *env, char *str, int i)
{
    t_list  *list;

    if (env->command_list == NULL)
    {
        env->command_list = ft_lstnew(str, i);
        return ;
    }
    list = env->command_list;
    while (list->next != NULL)
        list = list->next;
    list->next = ft_lstnew(str, i);
}

void        command_parse(t_env *env)
{
    char    *s1;
    size_t  i;
    size_t  off_set;

     i = 0;
    s1 = env->buffer;
    while (s1[i] != '\0')
    {
        off_set = 0;
        if (s1[i] != '\0' && ft_strchr(DELIMITER, s1[i]))
        {
            append_list(env, &s1[i], 1);
            i++;
        }
        else if (s1[i] != '\0' && !ft_strchr(DELIMITER, s1[i]))
        {
            while(s1[i + off_set] != '\0' && !ft_strchr(DELIMITER, s1[i + off_set]))
                off_set++;
            append_list(env, &s1[i], off_set);
            i += off_set;
        }
    }
}

int         param_check(char *word, t_list *env_base)
{
    if (ft_strstr(word, env_base->content))
        return (1);
    return (0);
}

void        expand_variable(t_list *command, t_list *var)
{
    t_list  *temp;
    t_list  *temp_one;
    char    *special;

    special = ft_strchr(command->content, ENVVARCHR);
    while (var != NULL)
    {
        temp_one = temp->content;
        if (special == command->content) //at beginning
        {
            if (temp->next != NULL)
            {
                free(command->content);
                command->content = ft_strdup(temp->next->content);
                return ;
            }
        }
        else //in middle
        {
            if (temp->next != NULL)
            {
                special[0] = '\0';
                command->content = ft_strnjoin( command->content, temp->next->content,1);
                return ;
            }
        }   
        var = var->next;
    }
}

void        free_command_list(t_env *env)
{
    t_list  *list;
    t_list  *last;

    if (env != NULL && env->argv_ptr != NULL)
    {
        free((void*)(env->argv_ptr));
        env->argv_ptr = NULL;
    }

    if (env == NULL || env->command_list == NULL)
        return ;
    list = env->command_list;
    env->command_list = NULL;

    while (list != NULL)
    {
        last = list;
        list = list->next;
        if (last != NULL)
        {
            if (last->content != NULL)
                free(last->content);
            free(last);             //segfault is here 
        }
    }
}

void        command_expansion(t_env *env)
{
    t_list  *temp;
    t_list  *env_var;
    char    *param;

    temp = env->command_list;
    while (temp != NULL)
    {
        param = ft_strchr(temp->content, ENVVARCHR);
        if (param != NULL)
        {
            env_var = env->environ;
            while (env_var != NULL)
            {
                if (param_check(param + 1, env_var->content)) //temp: is user input, env_var: begining of env list
                    expand_variable(temp, env_var);              
                env_var = env_var->next;
            }
        }
        temp = temp->next;
    }
}

int         doubles_check(t_list *list)
{
    int     count;

    count = 0;
    while (list != NULL)
    {
        if (ft_strchr(list->content, '"'))
            count++;
        list = list->next;
    }
    if (count == 0)
        return (0);
    if (count % 2 == 0)
        return (1);
    return (-1);
}

void        quote_join(t_env *env)
{
    t_list  *start;
    t_list  *last;
    t_list  *current;
    char    *string;

    current = env->command_list;
    string = NULL;
    last = NULL;
    while (current->next != NULL)
    {
        if (last != NULL && ft_strchr(last->content, '"'))
            break ;
        last = current;
        current = current->next;
    }
    start = last;
    while (current != NULL && !ft_strchr(current->content, '"'))
    {
        if (string == NULL)
            string = ft_strdup(current->content);
        else
            string = ft_strnjoin(string, current->content, 1);
        last = current;
        current = current->next;
        free(last->content);
        free(last);
    }
        last = current;
        if ( current != NULL && current->next != NULL)
            current = current->next;
        else
            current = NULL;
        if (last != NULL)
        {
            free(last->content);
            free(last);
        }
        if (start != NULL)
        {
            free(start->content);
        }
        start->content = NULL;
        if (string != NULL)
            start->content = string;
        else
        {
            start->content = ft_strdup(" ");
        }
        start->next = current;
        if (start->next != NULL)
            quote_join(env);
}

void        white_space_trimming(t_env *env)
{
    t_list *current;
    t_list *temp;

    current = env->command_list;
    while(current != NULL)
    {
        if (current->next != NULL && ft_strstr(current->next->content, " ") && ft_strlen(current->next->content) == 1)
        {
            temp = current->next;
            if (temp->next != NULL)
                current->next = temp->next;
            else
                current->next = NULL;
            ft_bzero(temp->content, ft_strlen(temp->content));
            free(temp->content);
            ft_bzero(temp, sizeof(t_list));
            free(temp);
            continue;
        }
        else
            current = current->next;
    }
}

void        make_char_ptr(t_env *env)
{
    int     count;
    t_list  *list;
    char    **temp;

    list = env->command_list;
    count = 1;
    while (list != NULL)
    {
        list = list->next;
        count++;
    }
    temp = (char**)ft_memalloc(sizeof(char*) * count);
    count = 0;
    list = env->command_list;
    while(list != NULL)
    {
        temp[count] = list->content;
        count++;
        list = list->next;
    }
    temp[count] = NULL;
    env->argv_ptr = temp;
}

void        print_list(t_list *list)
{
    while(list != NULL)
    {
        printf("'%s'\n", list->content);
        list = list->next;
    }
}

int     ft_echo(t_env *env, char **argv_ptr)
{
    int i;
    int count;

    count = 0;
    i = 1;
    while (argv_ptr[count] != NULL)
    {
        ft_putstr(argv_ptr[count]);
        count++;
        if (argv_ptr[count] != NULL)
            ft_putchar(' ');
    }
    return (i);
}

int     ft_cd(t_env *env, char **argv_ptr)
{
    int i;

    i = 1;
    return (i);
}

t_list      *variable_exists(char *str, t_list *environ)
{
    t_list  *name;

    while (environ != NULL)
    {
        if (environ->content != NULL)
        {
            name = environ->content;
            if (ft_strstr(str, name->content))// && ft_strlen(name->content) == ft_strlen(str))
                return (environ);
        }
        environ = environ->next;
    }
    return (NULL);
}

void        add_var(char *str, t_list *environ)
{
    t_list      *temp;
    
    temp = environ;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = ft_lstnew(NULL, 0);
    temp->content = ft_lstnew(str, ft_strlen(str));
}

void    add_value(char *var, char *value, t_list *environ)
{
    t_list  *temp;

    temp = variable_exists(var, environ);
    if (temp == NULL)
        return ;
    temp = temp->content;
    temp->next = ft_lstnew(value, ft_strlen(value));      
}

void        free_value(t_list *list)
{
    t_list *temp;

    list = list->content;
    temp = list->content; 
    if (list->next == NULL)
        return ;
    temp = list->next;
    list->next = NULL;
    while (temp != NULL)
    {
        list = temp;
        temp = temp->next;
        if (list != NULL)
        {
            free(list->content);
            free(list);
        }
    }
}

int     ft_setenv(t_env *env, char **argv_ptr)
{
    int i;
    int count;

    i = 1;
    count = 0;
    while(argv_ptr[count] != NULL)
        count++;
    if (count > 3)
    {
        printf("setenv : too many arguments.");
        return (-1);
    }
    if (count == 1)
        ft_env(env, argv_ptr);
    else
    {
        if (!variable_exists(argv_ptr[1], env->environ))
            add_var(argv_ptr[1], env->environ);
        else if (count == 2 && variable_exists(argv_ptr[1], env->environ))
            free_value(variable_exists(argv_ptr[1], env->environ));
        if (count == 3)
            add_value(argv_ptr[1], argv_ptr[2], env->environ);
    }
    return (i);
}


int     ft_unsetenv(t_env *env, char **argv_ptr)
{
    int i;

    i = 1;
    return (i);
}


int     ft_env(t_env *env, char **argv_ptr)
{
    int     i;
    t_list  *range;
    t_list  *domain;

    range = env->environ;
    i = 1;
    while (range != NULL)
    {
        domain = range->content;
        if (domain != NULL)
        {
            ft_putstr(domain->content);
            ft_putchar('=');
            domain = domain->next;
        }
        if (domain == NULL)
            ft_putchar('\n');
        while (domain != NULL)
        {            
            printf("%s\n", domain->content);
            domain = domain->next;
        }
        range = range->next;
    }
    return (i);
}


int     ft_exit(t_env *env, char **argv_ptr)
{
    int i;

    i = 1;
    env->flag = EXIT_CODE;
    return (i);
}

char *g_builtin[] = { NULL, "echo", "cd", "setenv", "unsetenv", "env", "exit", NULL};

int		(*g_func[]) (t_env *env, char **user_input) = { NULL, ft_echo, ft_cd, ft_setenv, ft_unsetenv, ft_env, ft_exit};

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

int         execute_command(t_env *env, char **argv_ptr)
{
    int     ret;

    ret = 0;
    if (argv_ptr[0] != NULL && is_builtin(argv_ptr[0]))
    {
        ret = (g_func[is_builtin(argv_ptr[0])])(env, argv_ptr);
    }
    else if (argv_ptr[0] != NULL)
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
    int     temp;

    ret = 0;
    while ((env->flag != EXIT_CODE) && read_line(env))
    {
        command_parse(env);
        temp = doubles_check(env->command_list);
        if(temp == -1)    //make sure to take proper account of ""
        {
            printf("Sorry Wrong number of quotes\n");
            continue;
        }
        if(temp == 1)
            quote_join(env);        //join all commands that are within the quotes and remove quotes
        white_space_trimming(env); //trim multiple white space items not in quotes

        //print_list(env->command_list);

        command_expansion(env);
        make_char_ptr(env);       //make a char **ptr that connects all contents in command_list
        ret = execute_command(env, env->argv_ptr);
    
        //here do a check to make sure anything program was ran

        // t_list *derps;
        // derps = env->command_list;
        // while(derps != NULL)
        // {
        //     printf("'%s'\n", derps->content);
        //     derps = derps->next;
        // }
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
    env.argv_ptr = NULL;

    
    ret = shell_loop(&env);
    return (ret);
}


/****************
 *                      gcc take2.c -g includes/mini_shell.h libft/libft.a
 * 
 * 
 *                  start on line 446
 *                      
 *                      need to finish the built in commands
 *                                          
 *                  
 *                                                                              
 *                          
 * 
 * 
 * 
 * 
 * **********************/