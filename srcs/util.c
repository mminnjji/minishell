/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:42:41 by man               #+#    #+#             */
/*   Updated: 2023/12/21 11:15:11 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_flag(char *str, int flag[], int i)
{
	char	c;

	c = str[i];
	if (str[i] < 0)
		c = str[i] * -1;
	if ((!flag[0] && !flag[1]) && (str[i] == '\"' || str[i] == '\''))
		flag[c % 2] = 1 - flag[c % 2];
	else if (flag[c % 2] && (str[i] == '\'' || str[i] == '\"'))
		flag[c % 2] = 1 - flag[c % 2];
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
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

void	minishell_free_util(t_cmd **tmp)
{
	int		i;

	if ((*tmp)->init_cmd)
		ft_free2((void **)&((*tmp)->init_cmd));
	if ((*tmp)->cmd)
	{
		i = -1;
		while ((*tmp)->cmd[++i])
			if ((*tmp)->cmd[i] != (*tmp)->cmd_path)
				ft_free2((void **)&((*tmp)->cmd[i]));
		ft_free2((void **)&((*tmp)->cmd));
	}
	if ((*tmp)->cmd_path)
		ft_free2((void **)&((*tmp)->cmd_path));
}

int	minishell_free(t_cmd **start, int flag)
{
	t_cmd	*tmp;
	t_cmd	*n;

	if (flag)
		g_exit_code = 1;
	tmp = (*start);
	if (!tmp)
		return (0);
	while (tmp)
	{
		n = tmp->next;
		if (tmp->infile != 0 && tmp->infile != -1)
			close(tmp->infile);
		if (tmp->outfile != 1 && tmp->outfile != -1)
			close(tmp->outfile);
		minishell_free_util(&tmp);
		ft_free2((void **)&tmp);
		tmp = n;
	}
	return (0);
}

int	print_error(void)
{
	perror("Error");
	return (0);
}
