/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheekan <jiheekan@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:17:22 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 20:17:24 by jiheekan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_error(char old[1024], char new[1024], t_env *envs)
{
	if (g_exit_code != 1)
	{
		getcwd(new, 1024);
		if (same_key(ft_strjoin("PWD=", new, 0, 0), envs) == -1 || \
		same_key(ft_strjoin("OLDPWD=", old, 0, 0), envs) == -1)
			return (-1);
	}
	return (1);
}

int	ft_error(t_cmd *cmd, char *message, int code, int ret)
{
	if (cmd)
	{
		write(2, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
		write(2, ": command not found\n", 20);
	}
	else if (message)
		write(2, message, ft_strlen(message));
	else
		perror(NULL);
	if (code >= 0)
		g_exit_code = code;
	if (ret)
		return (1);
	return (0);
}

void	cmd_error(t_cmd *curr)
{
	if (!curr->cmd || !*curr->cmd)
		exit(0);
	if (curr->cmd_path)
	{
		if (!ft_strcmp(curr->cmd[0], "."))
		{
			ft_error(0, "filename argument required\n", 2, 0);
			exit(2);
		}
		if (!ft_strcmp(curr->cmd[0], ".."))
		{
			ft_error(0, "command not found\n", 127, 0);
			exit(127);
		}
		ft_error(0, 0, -1, 0);
		exit(126);
	}
	ft_error(curr, 0, -1, 0);
	exit(127);
}
