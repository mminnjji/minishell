/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:36:52 by man               #+#    #+#             */
/*   Updated: 2023/12/18 16:06:56 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_freee(char **str)
{
	size_t	j;

	j = 0;
	while (str[j])
	{
		ft_free2((void **)&str[j]);
		j++;
	}
	ft_free2((void **)&str);
	return (NULL);
}

t_cmd	*init_node(int idx)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->init_cmd = NULL;
	node->cmd = NULL;
	node->infile = 0;
	node->outfile = 1;
	node->idx = idx;
	node->cmd_path = NULL;
	node->next = NULL;
	node->heredoc_flag = 0;
	return (node);
}

int	check_pipe_quote(char *str, char c, int flag[])
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	flag[0] = 0;
	flag[1] = 0;
	while (str[++i])
	{
		check_flag(str, flag, i);
		if (str[i] == c && flag[0] == 0 && flag[1] == 0)
		{
			count++;
			while (str[i + 1] == ' ')
				i++;
			if (c == '|' && str[i + 1] == c)
				return (-1);
		}
	}
	if (flag[0] == 1 || flag[1] == 1)
		return (-1);
	return (count);
}

int	get_malloc_list(char *str, t_cmd **start)
{
	int		i;
	int		count;
	t_cmd	*tmp;
	int		flag[2];

	tmp = *start;
	count = check_pipe_quote(str, '|', flag);
	if (count < 0)
	{
		g_exit_code = 127;
		write(2, "syntax error\n", 13);
		return (-2);
	}
	i = 0;
	while (i++ < count)
	{
		tmp->next = init_node(i);
		if (!(tmp->next))
		{
			g_exit_code = 1;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (count);
}
