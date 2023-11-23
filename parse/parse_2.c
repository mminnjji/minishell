#include "../includes/minishell.h"

int parse_by_space(t_cmd **start)
{
    t_cmd *tmp;

    tmp = (*start);
    while (tmp)
    {
        tmp->arg->parse = ft_split(tmp->arg->init_cmd, ' ');
        tmp = tmp->next;
    }
    return (0);
}