#include <../includes/mini_shell.h>

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