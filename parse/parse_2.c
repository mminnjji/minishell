#include "../includes/minishell.h"

char *get_str(char *str, int k, int tmp, char *res)
{
    int j;

    j = 0;
    while (j < k - tmp)
    {
        res[j] = str[j + tmp];
        j++;
    }
    res[j] = 0;
    return (res);
}

char *get_len(char *str, int *k, int *tmp)
{
    char *res;
    int flag[2];

    flag[0] = 0;
    flag[1] = 0;
    while (str[*k] == ' ')
        (*k)++;
    *tmp = *k;
    while (str[*k] && (str[*k] != ' ' || flag[0] == 1 || flag[1] == 1))
    {
        if (str[*k] == '\"' || str[*k] == '\'')
            flag[str[*k] % 2] = 1 - flag[str[*k] % 2];
        (*k)++;
    }
    res = (char *)malloc(sizeof(char) * (*k - *tmp + 1));
    return (res);
}

int set_space_parse(char ***parse, char *str)
{
    int i;
    int k;
    int tmp;

    i = 0;
    k = 0;
    while (i < count_str(str, ' '))
    {
        (*parse)[i] = get_len(str, &k, &tmp);
        if (!(*parse)[i])
            return (1);
        (*parse)[i] = get_str(str, k, tmp, (*parse)[i]);
        i++;
    }
    (*parse)[i] = 0;
    return (0);
}

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