#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

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

int get_malloc_list(char *str, t_cmd *start) //ㄹㅇ 완벽 ㄷㄷ
{
    int i;
    int count;
    int flag;
    t_cmd *tmp;

    i = -1;
    count = 0;
    flag = 0;
    tmp = start;
    while (str[++i])
    {
        if (str[i] == '\"' || str[i] == '\'') // 따옴표 열림/닫힘시 플래그 변경
            flag = 1 - flag;
        if (str[i] == '|' && flag == 0) //따옴표 안이 아닐 경우에만 파싱가능으로 판단
            count++;
        if (str[i] == '|' && str[i + 1] == '|' && flag == 0)
        {
            printf("syntax error\n");
            return (-1);
        }
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

void parse_by_pipe(int pipe_locate[], char *str, t_cmd *start, int pipe_num)
{
    int i;
    t_cmd *tmp;

    i = 0;
    tmp = start;
    while (start && i < pipe_num + 1)
    {
        start->arg = malloc(sizeof(t_arg));
        start->arg->first_cmd = malloc(sizeof(char) * (pipe_locate[i + 1] - pipe_locate[i] + 2));
        ft_strlcpy(start->arg->first_cmd, (const char *)(str + pipe_locate[i]), pipe_locate[i + 1] - pipe_locate[i] + 1);
        if (start->arg->first_cmd[strlen(start->arg->first_cmd) - 1] == '|')
            start->arg->first_cmd[strlen(start->arg->first_cmd) - 1] = 0;
        //printf("str : %s pipe0: %d pipe1: %d\n", start->arg->first_cmd, pipe_locate[i], pipe_locate[i + 1]);
        start = start->next;
        i++;
    }
    start = tmp;
}

//pipe 위치를 기준으로 파싱하여 구조체에 넣어줌
void get_init_cmd_list(char *str, t_cmd *start, int pipe_num) 
{
    int i;
    int j;
    int flag;
    int pipe_locate[pipe_num + 2];

    i = -1;
    j = 0;
    flag = 0;
    pipe_locate[0] = 0;
    while (str[++i])
    {
        if (str[i] == '\"' || str[i] == '\'') // 따옴표 열림/닫힘시 플래그 변경
            flag = 1 - flag;
        if (str[i] == '|' && flag == 0) //따옴표 안이 아닐 경우에만 파싱가능으로 판단
            pipe_locate[++j] = i + 1;
    }
    pipe_locate[pipe_num + 1] = i;
    parse_by_pipe(pipe_locate, str, start, pipe_num);
}

// 실행부
void work_cmd(char *str)
{
    t_cmd *start;
    int pipe_count;

    start = malloc(sizeof(t_cmd));
    //말록오류 처리 필
    pipe_count = get_malloc_list(str, start); //start 시작노드 구조체 할당
    if (pipe_count < 0)
    {
        free(start);
        return ;
    }
    get_init_cmd_list(str, start, pipe_count);
}

int main(void)
{
    char *str;

    while (1)
    {
        str = readline("minishell-3.2$ "); //문자열 받아서 실행
        if (str)
            work_cmd(str);
        else
            break;
        add_history(str);
        free(str);
    }
    return (0);
}
