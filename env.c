#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*get_path(char **envp, char *str)
{
    int i;

	while (*envp)
    {
        while (str[i])
        {
            if ((*envp)[i] != str[i])
                break;
            i++;
        }
        if (i == strlen(str))
        {
            if ((*envp)[i] == '=')
                return ((*envp) + i + 1);
        }
		envp++;
    }
    return (NULL);
}
