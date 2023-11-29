#include "../includes/minishell.h"

int parse_by_space(t_cmd **start)
{
    t_cmd *tmp;

    tmp = (*start);
    while (tmp)
    {
        tmp->cmd = ft_split(tmp->init_cmd, ' ');
        if (!tmp->cmd)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}