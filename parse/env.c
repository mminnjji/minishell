#include "../includes/minishell.h"

char *append_str2(char **str, int i, char *tmp)
{
    int j;
    int k;
    char *res;

    j = 0;
    k = 0;
    res = malloc(sizeof(char) * (ft_strlen((*str)) + ft_strlen(tmp) + 1));
    while ((*str)[j])
    {
        if (j == i)
        {
            while (tmp[k])
            {
                res[j + k] = tmp[k];
                k++;
            }
        }
        res[j + k] = (*str)[j];
        j++;
    }
    res[j + k] = 0;
    return (res);
}

char *append_str(char **str, int i, char *tmp)
{
    int j;
    int k;
    char *res;

    j = 0;
    k = 0;
    if ((*str)[0] == 0)
    {
        free(*str);
        return (tmp);
    }
    res = malloc(sizeof(char) * (ft_strlen((*str)) + ft_strlen(tmp) + 1));
    while ((*str)[j])
    {
        if (j == i)
        {
            while (tmp[k])
            {
                res[j + k] = tmp[k];
                k++;
            }
        }
        res[j + k] = (*str)[j];
        j++;
    }
    res[j + k] = 0;
    free(*str);
    return (res);
}

char	*get_path(char **envp, char **str, int idx)
{
    int i;
    int j;
    char *res;

    i = 0;
    res = ft_itoa(exit_code);
    if ((*str)[0] == '?')
    {
        if (idx == 0)
            return (res);
        else
            return ("0");
    }
	while (envp[i])
    {
        j = 0;
        while ((*str)[j])
        {
            if (envp[i][j] != (*str)[j])
                break;
            j++;
        }
        if (j == ft_strlen((*str)))
        {
            if (envp[i][j] == '=')
            {
                free(*str);
                return (delete_char(&envp[i], 0, j + 1, 1));
            }
        }
		i++;
    }
    free(*str);
    return ("");
}
//j지점이 환경변수 바로 다음인덱스 녀석임 - 그러니 만약 tmp ~ j라면 3 ~ 5 // j - tmp + 2
char *get_env(char *str, int j)
{
    int tmp;
    int i;
    char *env;

    tmp = j;
    i = 0;
    if (str[j] == '?')
        return ("?");
    while (str[j])
    {
        if (str[j] == '\"' || str[j] == '\'' || str[j] == '$' || str[j] == ' ' || str[j] == '?')
            break;
        j++;
    }
    env = malloc(sizeof(char) * (j - tmp + 1));
    while (tmp < j)
    {
        env[i] = str[tmp];
        tmp++;
        i++;
    }
    env[i] = 0;
    return (env);
}

char *replace_env(char **str, int j, char **envp, int idx)
{
    char *env;
    char *rep;
    int len;

    env = get_env((*str), j + 1); // 환경변수가 가리키는 부분 찾기
    if (!env)
        return (NULL);
    len = ft_strlen(env);
    rep = get_path(envp, &env, idx);
    if (!rep)
        return (NULL);
    (*str) = delete_char(str, j, len + 1, 0);
    if (!(*str))
        return (NULL);
    (*str) = append_str(str, j, rep);
    if (!(*str))
        return (NULL);
    return (*str);
}