#include "minishell.h"

// 실행부
void work_cmd(char *str)
{
    t_cmd *start;
    int pipe_count;

    start = malloc(sizeof(t_cmd));
    //말록오류 처리 필
    pipe_count = get_malloc_list(str, start); //start 시작노드 구조체 할당
    if (pipe_count < 0) // 두개이상의 연속된 파이프 -> 신택스 에러로 cmd 종료 // 다음 cmd는 받을 수 있도록 처리
    {
        free(start);
        return ;
    }
    if (get_init_cmd_list(str, start, pipe_count)) // 파이프로 분할된 연결리스트에 파이프 기준으로 자른 문자열 삽입
    {
        //free(start_연결리스트); // 말록오류 발생했을 때.. 겟넥라처럼 죄다 해제해줘야됨.. 그와중에 .. 다음 리스트는 받아야함
        return ;
    }
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