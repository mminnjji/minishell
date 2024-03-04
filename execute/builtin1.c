/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheekan <jiheekan@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:47:22 by jiheekan          #+#    #+#             */
/*   Updated: 2023/11/17 20:47:24 by jiheekan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if ((!ft_strcmp(cmd->cmd[0], "echo") || !ft_strcmp(cmd->cmd[0], "cd") || \
	!ft_strcmp(cmd->cmd[0], "pwd") || !ft_strcmp(cmd->cmd[0], "export") || \
	!ft_strcmp(cmd->cmd[0], "unset") || !ft_strcmp(cmd->cmd[0], "env") || \
	!ft_strcmp(cmd->cmd[0], "exit")))
		return (1);
	return (0);
}

int	builtin(t_cmd *cmd, int pipefd[2], t_env **envs, int flag)
{
	if (!cmd->cmd || !*cmd->cmd)
		return (0);
	if (cmd->infile == -1 || cmd->outfile == -1)
		g_exit_code = 1;
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (-1);
	if (!ft_strcmp(cmd->cmd[0], "echo") \
	&& is_n(cmd->cmd[1]) && flag)
		return (ft_echo(cmd, pipefd, 0));
	if (flag && !ft_strcmp(cmd->cmd[0], "echo"))
		return (ft_echo(cmd, pipefd, 1));
	if (flag && !ft_strcmp(cmd->cmd[0], "cd"))
		return (ft_cd(cmd, *envs, 0));
	if (flag && !ft_strcmp(cmd->cmd[0], "pwd"))
		return (ft_pwd(cmd, pipefd));
	if (flag && !ft_strcmp(cmd->cmd[0], "export"))
		return (ft_export(cmd, envs, pipefd));
	if (flag && !ft_strcmp(cmd->cmd[0], "unset"))
		return (ft_unset(cmd, envs));
	if (flag && !ft_strcmp(cmd->cmd[0], "env"))
		return (ft_env(cmd, *envs, pipefd, 0));
	if (flag && !ft_strcmp(cmd->cmd[0], "exit"))
		return (ft_exit(cmd));
	return (is_builtin(cmd));
}

int	is_n(char *option)
{
	int	i;

	i = 0;
	if (!option)
		return (0);
	if (option[i] != '-')
		return (0);
	if (!option[1])
		return (0);
	while (*(option + ++i))
		if (*(option + i) != 'n')
			return (0);
	return (1);
}

int	ft_echo(t_cmd *cmd, int pipefd[2], int flag)
{
	int	i;

	i = 2 - flag;
	if (cmd->outfile == 1 && cmd->next)
		cmd->outfile = pipefd[1];
	while (!flag && is_n(cmd->cmd[i]))
		i++;
	while (cmd->cmd[i])
	{
		write(cmd->outfile, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 1)
		write(cmd->outfile, "\n", 1);
	return (1);
}

int	ft_cd(t_cmd *c, t_env *envs, char *tmp)
{
	char	old[1024];
	char	new[1024];

	getcwd(old, 1024);
	if (c->cmd[1] && c->cmd[1][0] == '~' && ft_strcmp(c->cmd[1], "~"))
	{
		tmp = c->cmd[1];
		c->cmd[1] = ft_strjoin(find_key(envs, "HOME") + 1, c->cmd[1] + 1, 0, 0);
		free(tmp);
	}
	if (!c->cmd[1] || !ft_strcmp(c->cmd[1], "~"))
	{
		if (chdir(find_key(envs, "HOME") + 1) != 0)
			ft_error(0, "cd: OLDPWD not set\n", 1, 0);
	}
	else if (!ft_strcmp(c->cmd[1], "-"))
	{
		if (chdir(find_key(envs, "OLDPWD") + 1) != 0)
			ft_error(0, "cd: OLDPWD not set\n", 1, 0);
	}
	else if (chdir(c->cmd[1]) != 0)
		ft_error(0, 0, 1, 0);
	return (cd_error(old, new, envs));
}
