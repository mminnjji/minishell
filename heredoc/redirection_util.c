/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:27:05 by man               #+#    #+#             */
/*   Updated: 2023/12/18 19:56:18 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_env(char **str, char **envp, int idx, int f)
{
	int	i;
	int	flag[2];

	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	while ((*str)[i])
	{
		check_flag(*str, flag, i);
		if (((*str)[i] == '$' && (f || flag[1] != 1)) && \
		!(((*str)[i + 1] == '\"' && flag[0]) \
		|| ((*str)[i + 1] == ' ') || !(*str)[i + 1]))
		{
			(*str) = replace_env(str, i, envp, idx);
			if (!(*str))
				return (1);
			i--;
		}
		i++;
	}
	return (0);
}

int	do_redirect_in(t_cmd **tmp, int i, char **envp)
{
	char	*str;
	int		flag[2];

	flag[0] = 1;
	flag[1] = 1;
	str = change_str(tmp, flag, i, envp);
	if (!str)
		return (1);
	(*tmp)->infile = open(str, O_RDONLY);
	ft_free2((void **)&str);
	if ((*tmp)->infile < 0)
		return (2);
	return (0);
}

int	do_redirect_out(t_cmd **tmp, int i, char **envp)
{
	char	*str;
	int		flag[2];

	flag[0] = 1;
	flag[1] = 1;
	str = change_str(tmp, flag, i, envp);
	if (!str)
		return (1);
	(*tmp)->outfile = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	ft_free2((void **)&str);
	if ((*tmp)->outfile < 0)
		return (2);
	return (0);
}

int	do_redirect_pout(t_cmd **tmp, int i, char **envp)
{
	char	*str;
	int		flag[2];

	flag[0] = 2;
	flag[1] = 1;
	str = change_str(tmp, flag, i, envp);
	if (!str)
		return (1);
	(*tmp)->outfile = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_free2((void **)&str);
	if ((*tmp)->outfile < 0)
		return (2);
	return (0);
}

int	do_redirect_heredoc(t_cmd **tmp, int i, char *name, char **envp)
{
	char	*str;
	int		flag[3];

	flag[0] = 2;
	flag[1] = 0;
	flag[2] = 0;
	str = change_str(tmp, flag, i, NULL);
	name = append_str2(&name, 12, ft_itoa((*tmp)->idx));
	if (!str)
		return (1);
	return (r_heredoc(tmp, str, name, envp));
}
