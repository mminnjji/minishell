/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:46:22 by man               #+#    #+#             */
/*   Updated: 2023/12/18 20:15:45 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirect_err(int err, int flag[])
{
	if (err == 2)
		flag[2] = 1;
	else if (err == 1)
	{
		g_exit_code = 1;
		return (1);
	}
	else if (err == 3)
	{
		g_exit_code = 127;
		write(2, "syntax error\n", 13);
		return (1);
	}
	return (0);
}

int	do_redirect(t_cmd **tmp, int *i, char **envp, int flag)
{
	int		err;
	char	*name;
	int		here;

	name = "./heredoc_tmp ";
	err = 0;
	here = 0;
	if ((*tmp)->init_cmd[*i] == '<' && (*tmp)->init_cmd[*i + 1] == '<')
	{
		err = do_redirect_heredoc(tmp, *i, name, envp);
		here = 1;
	}
	if (!flag)
	{	
		if ((*tmp)->init_cmd[*i] == '<' && (*tmp)->init_cmd[*i + 1] != '<')
			err = do_redirect_in(tmp, *i, envp);
		else if ((*tmp)->init_cmd[*i] == '>' && (*tmp)->init_cmd[*i + 1] != '>')
			err = do_redirect_out(tmp, *i, envp);
		else if ((*tmp)->init_cmd[*i] == '>' && (*tmp)->init_cmd[*i + 1] == '>')
			err = do_redirect_pout(tmp, *i, envp);
	}
	if (!flag || here)
		(*i)--;
	return (err);
}

void	err_redirect(t_cmd **tmp, int flag[])
{
	if (flag[2])
	{
		perror("Error");
		g_exit_code = 1;
		(*tmp)->infile = -1;
		(*tmp)->outfile = -1;
		flag[2] = 0;
	}
	(*tmp) = (*tmp)->next;
}

int	check_redirect(t_cmd **start, char **envp)
{
	t_cmd	*tmp;
	int		i;
	int		f[3];

	f[0] = 0;
	f[1] = 0;
	f[2] = 0;
	tmp = *start;
	if (check_redirect_err(init_error(tmp), f))
		return (1);
	tmp = *start;
	while (tmp)
	{
		i = -1;
		while (tmp->init_cmd[++i])
		{
			check_flag(tmp->init_cmd, f, i);
			if ((tmp->init_cmd[i] == '<' || tmp->init_cmd[i] == '>') \
			&& f[0] == 0 && f[1] == 0)
				if (check_redirect_err(do_redirect(&tmp, &i, envp, f[2]), f))
					return (1);
		}
		err_redirect(&tmp, f);
	}
	return (0);
}
