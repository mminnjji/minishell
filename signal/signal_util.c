/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:40:09 by man               #+#    #+#             */
/*   Updated: 2023/12/18 15:22:26 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_cmd(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 1;
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_dfl(int signum)
{
	if (signum == SIGINT)
		g_exit_code = 130;
	else if (signum == SIGQUIT)
		g_exit_code = 131;
}

void	signal_dfl2(int signum)
{
	(void)signum;
	write(2, "\n", 1);
}

void	signal_heredoc_cmd(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 1;
		write(2, "\n", 1);
		close(0);
	}
}

void	check_fork_signal(void)
{
	if (g_exit_code == 131 || g_exit_code == 130)
	{
		if ((g_exit_code & 127) == 2)
			write(2, "\n", 1);
		else if ((g_exit_code & 127) == 3)
			write(2, "Quit: 3\n", 8);
	}
}
