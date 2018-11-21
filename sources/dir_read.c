#include <../includes/mini_shell.h>

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