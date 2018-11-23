#include "../includes/mini_shell.h"/*
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