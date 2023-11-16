#include "minishell.h"

// 파이프 기준으로 연결리스트 할당
int get_malloc_list(char *str, t_cmd *start)
{
    int i;
    int count;
    int flag[2];
    t_cmd *tmp;

    i = -1;
    count = 0;
    flag[0] = 0;
    flag[1] = 0;
    tmp = start;
    while (str[++i])
    {
        if (str[i] == '\"')
            flag[0] = 1 - flag[0];
        if (str[i] == '\'')
            flag[1] = 1 - flag[1];
        if (str[i] == '|' && flag[0] == 0 && flag[1] == 0) //따옴표 안이 아닐 경우
        {
            count++;
            while (str[i + 1] == ' ')
                i++;
            if (str[i + 1] == '|') // 연속된 파이프가 등장할 경우
            {
                printf("syntax error\n");
                return (-1);
            }
        }
        if (flag[0] * flag[1] == 1) // 따옴표 안 닫혔는데 .. 새로 다른 따옴표 열렸을 경우
        {
            printf("syntax error\n");
            return (-1);
        }
    }
    if (flag[0] == 1 || flag[1] == 1) // 따옴표 안닫혔을 경우
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

int parse_by_pipe(int pip[], char *str, t_cmd *start, int pipe_n)
{
    int i;
    t_cmd *tmp;
    t_arg *des;

    i = 0;
    tmp = start;
    while (start && i < pipe_n + 1)
    {
        des = start->arg;
        des = malloc(sizeof(t_arg));
        if (!des)
            return (1); // 이경우에 이전에 할당된 구조체 연결리스트 + 구조체 참조 구조체 arg + arg str 모두 해제해줘야함
        des->init_cmd = malloc(sizeof(char) * (pip[i + 1] - pip[i] + 2));
        if (!des->init_cmd)
            return (1); // 동일
        ft_strlcpy(des->init_cmd, (const char *)(str + pip[i]), pip[i + 1] - pip[i] + 1);
        if (des->init_cmd[strlen(des->init_cmd) - 1] == '|')
            des->init_cmd[strlen(des->init_cmd) - 1] = 0;
        printf("str : %s pipe0: %d pipe1: %d\n", des->init_cmd, pip[i], pip[i + 1]);
        start = start->next;
        i++;
    }
    start = tmp;
    return (0);
}

static int	get_line(char const *str, char c)
{
	int	i;
	int	count;
    int flag;

	count = 0;
	i = 0;
    flag = 0;
	while (str[i])
	{
		while (str[i] == c && flag == 0)
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while ((str[i] != c && str[i]) || flag == 1)
            {
                if (str[i] == '"')
                i++;
            }
		}
	}
	return (count);
}

int parse_by_space(t_cmd *start)
{
    t_arg *des;
    int flag[2];
    int i;

    i = 0;
    flag[0] = 0;
    flag[1] = 0;
    des = start->arg;
    des->parse = (char **)malloc((get_line(des->init_cmd, ' ') + 1) * sizeof(char *));
    while (des->init_cmd[i])
    {
        if (des->init_cmd[i] == '\"')
            flag[0] = 1 - flag[0];
        if (des->init_cmd[i] == '\'')
            flag[1] = 1 - flag[1];
        if (des->init_cmd[i] == ' ')
        {
            while (des->init_cmd[i] == ' ')
                i++;
        }
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
    if (parse_by_pipe(pip, str, start, pipe_n))
        return (1);
    return (0);
}
