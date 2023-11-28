#include "../includes/minishell.h"

//pipe 위치를 기준으로 파싱하여 구조체에 넣어줌
void make_pipe(int pip[], char *str, int pipe_n) 
{
    int i;
    int j;
    int flag[2];

    i = -1;
    j = 0;
    flag[0] = 0;
    flag[1] = 0;
    pip[0] = 0;
    while (str[++i])
    {
        if (str[i] == '\"')
            flag[0] = 1 - flag[0];
        if (str[i] == '\'')
            flag[1] = 1 - flag[1];
        if (str[i] == '|' && flag[0] == 0 && flag[1] == 0) //따옴표 안이 아닐 경우에만 파싱가능으로 판단
            pip[++j] = i + 1;
    }
    pip[pipe_n + 1] = i;
}

int parse_by_pipe(char *str, t_cmd **start, int pipe_n)
{
    int i;
    int pip[pipe_n + 2];
    t_cmd *tmp;

    make_pipe(pip, str, pipe_n);
    i = 0;
    tmp = (*start);
    while (tmp && i < pipe_n + 1)
    {
        tmp->init_cmd = malloc(sizeof(char) * (pip[i + 1] - pip[i] + 2));
        if (!tmp->init_cmd)
            return (1); // 동일
        ft_strlcpy(tmp->init_cmd, (const char *)(str + pip[i]), pip[i + 1] - pip[i] + 1);
        if (tmp->init_cmd[strlen(tmp->init_cmd) - 1] == '|')
            tmp->init_cmd[strlen(tmp->init_cmd) - 1] = 0;
        tmp = tmp->next;
        i++;
    }
    return (0);
}
