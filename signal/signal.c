/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:05:46 by man               #+#    #+#             */
/*   Updated: 2023/12/13 15:50:04 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_signal_off(void)
{
	struct termios	t;

	tcgetattr(1, &t);
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &t);
}

void	print_signal_on(void)
{
	struct termios	t;

	tcgetattr(1, &t);
	t.c_lflag |= (ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &t);
}

void	signal_check1(int flag)
{
	if (!flag)
	{
		print_signal_on();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (flag == 1)
	{
		print_signal_off();
		signal(SIGINT, signal_cmd);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 2)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	signal_check2(int flag)
{
	if (flag == 3)
	{
		print_signal_off();
		signal(SIGINT, signal_heredoc_cmd);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 4)
	{
		signal(SIGINT, signal_dfl);
		signal(SIGQUIT, signal_dfl);
	}
	else if (flag == 5)
	{
		signal(SIGINT, signal_dfl2);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	signal_check(int flag)
{
	signal_check1(flag);
	signal_check2(flag);
}
