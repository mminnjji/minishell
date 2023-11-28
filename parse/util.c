#include "../includes/minishell.h"
// 스트링 복사
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (src[l] != '\0')
		l++;
	if (size != 0)
	{
		while ((src[i] != '\0') && (i + 1 < size))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (l);
}

int minishell_free(t_cmd **start)
{
    t_cmd *tmp;
    t_cmd *n;

    tmp = (*start);
    while (tmp)
    {
        n = tmp->next;
        free(tmp);
        tmp = n;
    }
    start = NULL;
    perror("Error");
    return(0);
}

int print_error(void)
{
    perror("Error");
    return (0);
}