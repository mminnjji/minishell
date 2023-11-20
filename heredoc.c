#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// i 인덱스 문자 delete 하고 앞으로 당긴 새로운 문자열 생성
char *delete_char(char *str, int i)
{
    int j;
    int k;
    char *res;

    res = malloc(sizeof(char) * strlen(str) + 1);
    j = 0;
    k = 0;
    while (str[j])
    {
        if (j == i)
            j++;
        res[k] = str[j];
        k++;
        j++;
    }
    res[j] = 0;
    free(str);
    return (res);
}

//따옴표를 없애줘요 아주 아름답게.. 연결해줌
char *remove_quote(char *str)
{
    int i;
    int len;
    int count;

    i = 0;
    count = 0;
    len = strlen(str);
    while (i < strlen(str) - count)
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            count++;
            str = delete_char(str, i);
            i--;
        }
        i++;
    }
    str[i] = 0;
    return (str);
}

//진짜. 히어독 -> 스트링이랑 비교해서 같은게 있을 때 탈출시켜줌 -> 이전 문자열 임시파일 저장
int here_doc(char *str)
{
    int file;
    char *line;

    unlink(".heredoc_tmp");
    file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
    if (file < 0)
        return (1);
    while (1)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line)
            return (0);
        if (!ft_strncmp(str, line, ft_strlen(str)) && ft_strlen(str) == (ft_strlen(line) - 1))
            break;
        write(file, line, ft_strlen(line));
        free(line);
    }
    free(line);
    close(file);
    return (0);
}

// 히어독을 발견했을 때의 마음가짐 - 스트링의 n번째부터 공백/따옴표 계산해서 대조할 문자열 생성
char *get_heredoc(char *str, int n)
{
    int i;
    int j;
    int flag[2];
    char *res;

    i = 0;
    j = -1;
    flag[0] = 0;
    flag[1] = 0;
    while (str[n + i] == ' ')
            n++;
    while (str[n + i])
    {
        if (str[n + i] == '\"' || str[n + i] == '\'')
            flag[str[n + i] % 2] = 1 - flag[str[n + i] % 2];
        if (flag[0] == 0 && flag[1] == 0 && str[n + i] == ' ')
            break;
        i++;
    }
    res = malloc(sizeof(char) * (i + 1));
    while (++j < i)
        res[j] = str[n + j];
    res[j] = 0;
    return (res);
}


/*
// 히어독이 있니 => 있으면 실행을 해라
int check_heredoc(t_cmd **start)
{
    int i;
    int j;
    t_cmd *tmp;
    char *str;

    tmp = (*start);
    while (tmp)
    {
        i = 0;
        while (tmp->arg->init_cmd[i])
        {
            j = 0;
            if (ft_strcmp(tmp->arg->init_cmd + i, "<<", 2))
            {
                str = get_heredoc(tmp->arg->init_cmd, i);
                str = remove_quote(str);
                here_doc(str);
            }
            i++;
        }
        tmp = tmp ->next;
    }
    return (0);
}
*/

int check_heredoc(char *des)
{
    int i;
    int j;
    char *str;

    i = 0;
    while (des[i])
    {
        j = 0;
        if (ft_strcmp(des + i, "<<", 2))
        {
            str = get_heredoc(des, i);
            str = remove_quote(str);
            here_doc(str);
        }
        i++;
    }
    return (0);
}

int main()
{
    char *str = "hello <<cmd hello";
    check_heredoc(str);
    return (0)
}