/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:12:34 by man               #+#    #+#             */
/*   Updated: 2023/12/18 17:06:23 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quote(char *str)
{
	int	i;
	int	len;
	int	flag[2];
	int	quote;

	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		quote = flag[0] + flag[1];
		check_flag(str, flag, i);
		if (quote != flag[0] + flag[1])
		{
			str = delete_char(&str, i, 1, 0);
			if (!str)
				return (NULL);
			len = ft_strlen(str);
			i--;
		}
		i++;
	}
	return (str);
}

char	*make_str(t_cmd **tmp, int i, int n)
{
	int		j;
	char	*res;

	j = -1;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	while (++j < i)
		res[j] = (*tmp)->init_cmd[n + j];
	res[j] = 0;
	return (res);
}

char	*get_heredoc(t_cmd *tmp, int n, int *len, int flag[])
{
	int		i;
	int		j;

	i = -1;
	j = n;
	while (tmp->init_cmd[n] && tmp->init_cmd[n] == ' ')
		n++;
	(*len) = n - j + (*len);
	tmp->heredoc_flag = 0;
	while (tmp->init_cmd[n + ++i])
	{
		check_flag(tmp->init_cmd, flag, n + i);
		if (tmp->init_cmd[n + i] == '\"' || tmp->init_cmd[n + i] == '\'')
			tmp->heredoc_flag = 1;
		if (flag[0] == 0 && flag[1] == 0 && (tmp->init_cmd[n + i] == ' ' \
		|| tmp->init_cmd[n + i] == '<' || tmp->init_cmd[n + i] == '>'))
			break ;
		(*len)++;
	}
	return (make_str(&tmp, i, n));
}

int	ft_strncmp2(char *s1, char *s2, size_t n)
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
