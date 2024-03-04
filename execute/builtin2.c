/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheekan <jiheekan@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:34:50 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/06 20:34:58 by jiheekan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_cmd *cmd, t_env **envs, int pipefd[2])
{
	int	i;
	int	check;

	i = 0;
	if (!cmd->cmd[1])
		ft_env(cmd, *envs, pipefd, 1);
	check_export(cmd->cmd, 0, -1);
	while (cmd->cmd[++i])
	{
		check = same_key(ft_strdup(cmd->cmd[i], ft_strlen(cmd->cmd[i])), *envs);
		if ((cmd->cmd[i][0] == '=' || check) && check != -1)
			continue ;
		if (check == -1)
			return (-1);
		if (ft_lstadd_back(envs, \
		ft_lstnew(key(cmd->cmd[i]), val(cmd->cmd[i]), cmd->cmd[i])))
			return (-1);
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_env **envs)
{
	int	i;

	i = 0;
	if (!(*envs)->key)
		return (1);
	if (!cmd->cmd[1])
		return (1);
	check_export(cmd->cmd, 0, -1);
	i = 0;
	while (cmd->cmd[++i])
		delete_envs(cmd->cmd[i], envs, *envs, 0);
	return (1);
}

void	ft_env2(t_cmd *cmd, char **env, int flag)
{
	int	flag2;
	int	j;
	int	i;

	i = -1;
	while (env[++i])
	{
		j = -1;
		flag2 = 0;
		if (flag)
			sort(env);
		if (flag)
			write(cmd->outfile, "declare -x ", 11);
		while (env[i][++j])
		{
			write(cmd->outfile, &env[i][j], 1);
			if (env[i][j] == '=' && flag && !flag2)
				write(cmd->outfile, "\"", 1);
			if (env[i][j] == '=' && flag && !flag2)
				flag2 = 1;
		}
		if (flag && env[i] && ft_strchr(env[i], '='))
			write(cmd->outfile, "\"", 1);
		write(cmd->outfile, "\n", 1);
	}
}

int	ft_env(t_cmd *cmd, t_env *envs, int pipefd[2], int flag)
{
	char	**env;

	if (cmd->outfile == 1 && cmd->next)
		cmd->outfile = pipefd[1];
	if (cmd->cmd[1])
	{
		if (access(cmd->cmd[1], F_OK) == 0)
			ft_error(0, "Permission denied\n", 126, 0);
		else
			ft_error(0, 0, 127, 0);
		return (1);
	}
	if (!envs->key)
		return (1);
	env = change_env(envs, flag, envs, 0);
	if (!env)
		return (-1);
	ft_env2(cmd, env, flag);
	ft_free(&env);
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	unsigned char	exitcode;

	if (!cmd->cmd[1])
		exit (0);
	if (ft_strlen(cmd->cmd[1]) < 20 && \
	ft_atoi(cmd->cmd[1], 0, 1, 0))
	{
		if (cmd->cmd[2])
		{
			write(2, "exit: too many argumets\n", 24);
			g_exit_code = 1;
			return (1);
		}
		else
		{
			exitcode = (unsigned char)ft_atoi(cmd->cmd[1], 1, 1, 0);
			g_exit_code = (int)exitcode;
			exit (exitcode);
		}
	}
	write(2, "exit: ", 6);
	write(2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
	write(2, ": numeric argument required\n", 28);
	g_exit_code = 255;
	exit (255);
}
