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

// i 인덱스 문자 포함 n만큼 delete 하고 앞으로 당긴 새로운 문자열 생성
char *delete_char(char *str, int i, int n)
{
    int j;
    int k;
    int l;
    char *res;

    res = malloc(sizeof(char) * strlen(str) + 1);
    j = 0;
    k = 0;
    l = -1;
    while (str[j])
    {
        if (j == i)
        {   
            while (++l <= n)
                j++;
        }
        res[k] = str[j];
        k++;
        j++;
    }
    res[k] = 0;
    //free(str);
    printf("res: %s\n", res);
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
            str = delete_char(str, i, 1);
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
    while (str[n + i] && str[n + i] == ' ')
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
    //free(str);
    return (res);
}

// 히어독을 발견 -> fd 에 넣어주기 -> 리스트를 ,, 돌면서?웅.. 
// 그냥 인수 >> 리다이렉션 >> 히어독
int check_heredoc(t_cmd **start)
{
    int i;
    t_cmd *tmp;
    char *str;

    tmp = (*start);
    while (tmp)
    {
        i = 0;
        tmp->infile = 1; // stdin;
        printf("cmd : %s \n",tmp->arg->init_cmd);
        while (tmp->arg->init_cmd[i])
        {
            if (!ft_strncmp(tmp->arg->init_cmd + i, "<<", 2))
            {
                str = get_heredoc(tmp->arg->init_cmd, i + 2);
                str = remove_quote(str);
                delete_char(tmp->arg->init_cmd, i, strlen(str) + 1); // 히어독 없애버리기
                here_doc(str);
                tmp->infile = open(".heredoc_tmp", O_RDONLY); // 일단! 인파일 fd열고 시작
            }
            i++;
        }
        tmp = tmp ->next;
    }
    return (0);
}
