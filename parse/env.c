#include "../includes/minishell.h"

char	*get_path(char **envp, char *str)
{
    int i;

    i = 0;
	while (*envp)
    {
        while (str[i])
        {
            if ((*envp)[i] != str[i])
                break;
            i++;
        }
        if (i == ft_strlen(str))
        {
            if ((*envp)[i] == '=')
                return ((*envp) + i + 1);
        }
		envp++;
    }
    return (NULL);
}
