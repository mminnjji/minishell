#include "../includes/minishell.h"

int count_char(char *str, char c) // 파이프와 따옴표 확인
{
    int i;
    int flag[2];
    int count;

    i = -1;
    count = 0;
    flag[0] = 0;
    flag[1] = 0;
    while (str[++i])
    {
        if (str[i] == '\"' || str[i] == '\'')
            flag[str[i] % 2] = 1 - flag[str[i] % 2];
        if (str[i] == c && flag[0] == 0 && flag[1] == 0) //따옴표 안이 아닐 경우
        {
            count++;
            while (str[i + 1] == ' ')
                i++;
            if (c == '|' && str[i + 1] == c) // 연속된 파이프가 등장할 경우
                return (-1);
        }
        if (flag[0] * flag[1] == 1) // 따옴표 안 닫혔는데 .. 새로 다른 따옴표 열렸을 경우
            return (-1);
    }
    if (flag[0] == 1 || flag[1] == 1) // 따옴표 안닫혔을 경우
        return (-1);
    return (count);
}

// 파이프 기준으로 연결리스트 할당
int get_malloc_list(char *str, t_cmd *start)
{
    int i;
    int count;
    t_cmd *tmp;

    tmp = start;
    count = count_char(str, '|'); // 파이프 개수 세기 - 따옴펴/연속파이프 처리
    if (count < 0)
    {
        printf("syntax error\n");
        return (-1);
    }
    i = 0;
    while (i++ < count)
    {
        start->arg = malloc(sizeof(t_arg));
        start->next = malloc(sizeof(t_cmd));
        start = start->next;
    }
    start->next = NULL;
    start = tmp;
    return (count);
}

int parse_by_pipe(int pip[], char *str, t_cmd **start, int pipe_n)
{
    int i;
    t_cmd *tmp;

    i = 0;
    tmp = (*start);
    while (tmp && i < pipe_n + 1)
    {
        tmp->arg = malloc(sizeof(t_arg));
        if (!tmp->arg)
            return (1); // 이경우에 이전에 할당된 구조체 연결리스트 + else 해제
        tmp->arg->init_cmd = malloc(sizeof(char) * (pip[i + 1] - pip[i] + 2));
        if (!tmp->arg->init_cmd)
            return (1); // 동일
        ft_strlcpy(tmp->arg->init_cmd, (const char *)(str + pip[i]), pip[i + 1] - pip[i] + 1);
        if (tmp->arg->init_cmd[strlen(tmp->arg->init_cmd) - 1] == '|')
            tmp->arg->init_cmd[strlen(tmp->arg->init_cmd) - 1] = 0;
        tmp = tmp->next;
        i++;
    }
    return (0);
}

//pipe 위치를 기준으로 파싱하여 구조체에 넣어줌
int get_init_cmd_list(char *str, t_cmd *start, int pipe_n) 
{
    int i;
    int j;
    int flag[2];
    int pip[pipe_n + 2];

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
    if (parse_by_pipe(pip, str, &start, pipe_n))
        return (1);
    if (check_redirect(&start))
        return (1);
    return (0);
}
