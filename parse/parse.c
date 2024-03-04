/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:29:54 by man               #+#    #+#             */
/*   Updated: 2023/12/21 11:24:33 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_pipe(int *pip, char *str, int pipe_n, int flag[])
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	pip[0] = 0;
	while (str[++i] == ' ')
		i++;
	if (str[i] == '|')
		return (1);
	while (str[++i])
	{
		check_flag(str, flag, i);
		if (str[i] == '|' && flag[0] == 0 && flag[1] == 0)
		{
			pip[++j] = i + 1;
			while (str[i + 1] == ' ')
				i++;
			if (!str[i + 1])
				return (1);
		}
	}
	pip[pipe_n + 1] = i;
	return (0);
}

int	parse_by_pipe(char *str, t_cmd **start, int pipe_n)
{
	int		i;
	int		*pip;
	int		flag[2];
	t_cmd	*tmp;

	pip = malloc(sizeof(int) * (pipe_n + 2));
	if (!pip)
		return (check_redirect_err(1, flag));
	if (make_pipe(pip, str, pipe_n, flag))
		return (ft_free2((void **) &pip) && check_redirect_err(3, flag));
	i = 0;
	tmp = (*start);
	while (tmp && i < pipe_n + 1)
	{
		tmp->init_cmd = malloc(sizeof(char) * (pip[i + 1] - pip[i] + 2));
		if (!tmp->init_cmd)
			return (check_redirect_err(1, flag));
		ft_strlcpy(tmp->init_cmd, str + pip[i], pip[i + 1] - pip[i] + 1);
		if (tmp->init_cmd[ft_strlen(tmp->init_cmd) - 1] == '|')
			tmp->init_cmd[ft_strlen(tmp->init_cmd) - 1] = 0;
		tmp = tmp->next;
		i++;
	}
	free(pip);
	return (0);
}

int	parse_by_space(t_cmd **start)
{
	t_cmd	*tmp;

	tmp = (*start);
	while (tmp)
	{
		tmp->cmd = ft_split2(tmp->init_cmd, ' ');
		if (!tmp->cmd)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	parse_by_quote_util(t_cmd **tmp, int flag[], int i, int *j)
{
	int	quote;

	quote = flag[0] + flag[1];
	check_flag((*tmp)->cmd[i], flag, (*j));
	if (quote != flag[0] + flag[1])
	{
		(*tmp)->cmd[i] = delete_char(&((*tmp)->cmd[i]), (*j), 1, 0);
		if (!(*tmp)->cmd[i])
			return (1);
		(*j)--;
	}
	return (0);
}

int	parse_by_quote(t_cmd **start, int flag[])
{
	int		i;
	int		j;
	t_cmd	*tmp;

	tmp = (*start);
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			j = -1;
			while (tmp->cmd[i][++j])
			{
				if (parse_by_quote_util(&tmp, flag, i, &j))
					return (1);
			}
		}
		tmp = tmp -> next;
	}
	return (0);
}
