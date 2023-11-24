#include "../includes/minishell.h"
// int exit_code
// 실행부
void work_cmd(char *str, char **envp)
{
    t_cmd *start;
    int pipe_count;

    start = malloc(sizeof(t_cmd));
    if (!start)
    {
        perror("Error:");
        return ;
    }
    pipe_count = get_malloc_list(str, start); //구조체 할당
    if (pipe_count < 0) // 두개이상의 연속된 파이프 -> 신택스 에러로 cmd 종료 // 다음 cmd는 받을 수 있도록 처리
    {
        free(start);
        return ;
    }
    if (get_init_cmd_list(str, start, pipe_count)) // 파이프로 분할된 연결리스트에 파이프 기준으로 자른 문자열 삽입
    {
        printf("file open fail\n");
        return ;
    }
    parse_by_space(&start);
    check_envp(&start, envp);
    parse_by_quote(&start);
    while (start)
    {
        int i = 0;
        while (start->cmd[i])
        {
            printf("pcmd: %s\n", start->cmd[i]);
            i++;
        }
        printf("cmd : %s in : %d, out : %d\n", start->init_cmd, start->infile, start->outfile);
        start = start->next;
    }
}

int main(int argc, char **argv, char *envp[])
{
    char *str;
    argc = 1;
    (void)argv;

    while (1)
    {
        str = readline("minishell-3.2$ "); //문자열 받아서 실행
        if (str)
            work_cmd(str, envp);// 문자열이 들어왔을 경우
        else
            break;
        add_history(str); // 스트링 히스토리 기록
        free(str);
    }
    return (0);
}