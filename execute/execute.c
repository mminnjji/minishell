/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:32:42 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/18 19:10:12 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_cmd *curr, int pipefd[2], t_env *envs)
{
	char	**env;

	env = change_env(envs, 0, envs, 0);
	if (curr->infile > 0)
		dup2(curr->infile, 0);
	if (curr->infile > 0)
		close(curr->infile);
	if (curr->outfile == 1 && curr->next)
		dup2(pipefd[1], 1);
	else if (curr->outfile != 1 && curr->outfile != -1)
		dup2(curr->outfile, 1);
	if (curr->outfile != 1 && curr->outfile != -1)
		close(curr->outfile);
	close(pipefd[1]);
	if (curr->infile == -1 || curr->outfile == -1 || !env)
		exit (1);
	if (curr->cmd && *curr->cmd)
		execve(curr->cmd_path, curr->cmd, env);
	cmd_error(curr);
}

void	ft_child(int pipefd[2], t_cmd **curr, t_env **envs)
{
	int	check;

	check = 0;
	signal_check(0);
	close(pipefd[0]);
	if (*(*curr)->cmd)
		check = builtin(*curr, pipefd, envs, 1);
	if (check == 0)
		exec_cmd(*curr, pipefd, *envs);
	if ((*curr)->infile > 0)
		dup2((*curr)->infile, 0);
	if ((*curr)->infile > 0)
		close((*curr)->infile);
	if ((*curr)->outfile != 1 && (*curr)->outfile != -1)
		close((*curr)->outfile);
	close(pipefd[1]);
	if (check == -1)
		exit (1);
	exit (g_exit_code);
}

int	execute3(t_cmd **curr, t_env **envs, int pipefd[2], int pid)
{
	int	status;

	signal_check(4);
	pid = fork();
	if (pid == -1)
		return (ft_error(0, 0, 1, 1));
	if (pid == 0)
		ft_child(pipefd, curr, envs);
	if (!(*curr)->next)
	{
		waitpid(pid, &status, 0);
		if (g_exit_code != 130 && g_exit_code != 131)
			g_exit_code = WEXITSTATUS(status);
		if (WTERMSIG(status) && (g_exit_code == 130 || g_exit_code == 131))
			check_fork_signal();
	}
	*curr = (*curr)->next;
	if (*curr && (*curr)->infile == 0)
		dup2(pipefd[0], (*curr)->infile);
	close(pipefd[1]);
	close(pipefd[0]);
	return (0);
}

void	execute2(t_cmd *cmd, t_env **envs, char ***myenv, t_cmd *curr)
{
	int		pipefd[2];

	while (curr)
	{
		g_exit_code = 0;
		if (*curr->cmd && !builtin(curr, pipefd, envs, 0))
			find_path1(*myenv, curr);
		if (pipe(pipefd) == -1)
		{
			ft_error(0, 0, -1, 0);
			return ;
		}
		if (*curr->cmd && !cmd->next)
		{
			if (builtin(cmd, pipefd, envs, 1) != 0)
			{
				ft_free(myenv);
				*myenv = change_env(*envs, 1, *envs, 0);
				return ;
			}
		}
		if (execute3(&curr, envs, pipefd, 0))
			return ;
	}
}

void	execute(t_cmd *cmd, char ***myenv)
{
	t_cmd	*curr;
	t_env	*envs;
	int		std_in;

	curr = cmd;
	g_exit_code = 0;
	envs = make_envs(*myenv, 0);
	if (!envs)
	{
		g_exit_code = 1;
		return ;
	}
	std_in = dup(0);
	execute2(cmd, &envs, myenv, cmd);
	dup2(std_in, 0);
	close(std_in);
	signal_check(5);
	while (waitpid(0, NULL, 0) > 0)
		;
	ft_lstclear(&envs);
}
