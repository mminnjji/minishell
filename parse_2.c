#include "minishell.h"

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
    printf("l : %d\n", check_quote_2(str, ' '));
    while (i < check_quote_2(str, ' '))
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

int parse_by_space(t_cmd **start, int pipe_n)
{
    int i;
    t_cmd *tmp;

    i = 0;
    tmp = (*start);
    while (tmp && i < pipe_n + 1)
    {
        tmp->arg->parse = malloc(sizeof(char *) * (check_quote(tmp->arg->init_cmd, ' ') + 2));
        set_space_parse(&(tmp->arg->parse), tmp->arg->init_cmd);
        i++;
        tmp = tmp->next;
    }
    return (0);
}