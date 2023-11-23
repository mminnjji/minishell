#include "../includes/minishell.h"

char	*get_path(char **envp, char **str)
{
    int i;

    i = 0;
	while (*envp)
    {
        while ((*str)[i])
        {
            if ((*envp)[i] != (*str)[i])
                break;
            i++;
        }
        if (i == (int)strlen((*str)))
        {
            if ((*envp)[i] == '=')
                return ((*envp) + i + 1);
        }
		envp++;
    }
    return ("");
}

void replace_char(char *env, char *r_env, int j)
{
    int i;

    i = 0;
    while (r_env[i])
    {
        env[j + i] = r_env[i]; // $~ 을 바꾸는 중,,
        i++;
    }
}

char *replace_env(char **str, int j, char **envp)
{
    int i;
    int l;
    int k;
    char *env;
    char *r_env;

    i = 0;
    l = -1;
    k = 0;
    while ((*str)[j + i + 1] && (*str)[j + i + 1] != '\'' && (*str)[j + i + 1] != '\"' \
    && (*str)[j + i + 1] != '$' && (*str)[j + i + 1] != ' ')
        i++;
    env = malloc(sizeof(char) * (i + 1));
    while (++l < i)
        env[l] = (*str)[j + l + 1];
    env[l] = 0;
    printf("env:%s\n", env);
    r_env = get_path(envp, &env);
    free(env);
    l = 0;
    env = malloc(sizeof(char) * (ft_strlen((*str)) + ft_strlen(r_env) - i + 1));
    while ((*str)[l])
    {
        if (l == j) 
        {
            replace_char(env, r_env, j);
            l = l + i + 1;
            k = k + ft_strlen(r_env);
        }
        else
        {
            env[k] = (*str)[l];   
            l++;
            k++;
        }
    }
    return (env);
}