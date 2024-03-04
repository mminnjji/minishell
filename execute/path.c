/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 01:29:57 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2, int i, int flag)
{
	char	*arr;
	int		j;

	j = -1;
	while (s1[i])
		i++;
	while (s2[++j])
		;
	arr = (char *)malloc(sizeof(char) * (j + i + flag + 1));
	if (!arr)
		return (0);
	j = -1;
	while (s1[++j])
		arr[j] = s1[j];
	if (flag)
		arr[i++] = '/';
	j = -1;
	while (s2[++j])
		arr[i++] = s2[j];
	arr[i] = 0;
	return (arr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*s3;
	unsigned char	*s4;

	i = 0;
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*(s3 + i) == *(s4 + i) && i < n - 1 && *(s3 + i) != '\0')
		i++;
	if (*(s3 + i) - *(s4 + i) == 0)
		return (0);
	return (1);
}

char	*addpath(char *only_cmd, int j, char **paths)
{
	int	i;

	i = 0;
	if (!only_cmd)
		return (only_cmd);
	while (*(only_cmd + i))
	{
		if (*(only_cmd + i) == '/')
			return (only_cmd);
		i++;
	}
	if (!paths)
		return (0);
	return (ft_strjoin(paths[j], only_cmd, 0, 1));
}

void	find_path2(t_cmd *cmd, char **paths)
{
	int		i;
	char	*cmd_path;
	char	*only_cmd;

	i = -1;
	only_cmd = cmd->cmd[0];
	cmd->cmd_path = 0;
	if (!paths && only_cmd[0])
		if (access(only_cmd, F_OK) == 0)
			cmd->cmd_path = only_cmd;
	if (!paths || !only_cmd[0])
		return ;
	while (paths[++i])
	{
		cmd_path = addpath(only_cmd, i, paths);
		if (!cmd_path)
			return ;
		if (access(cmd_path, F_OK) == 0)
		{
			cmd->cmd_path = cmd_path;
			return ;
		}
		if (cmd_path && only_cmd != cmd_path)
			free(cmd_path);
	}
}

void	find_path1(char **env, t_cmd *cmd)
{
	int		i;
	char	*all_path;
	char	**paths;

	i = -1;
	all_path = 0;
	paths = 0;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			all_path = ft_strdup(env[i] + 5, 0);
	if (all_path)
		paths = ft_split(all_path, ':');
	if (all_path && !paths)
	{
		free(all_path);
		return ;
	}
	find_path2(cmd, paths);
	if (all_path)
		free(all_path);
	all_path = 0;
	if (paths)
		ft_free(&paths);
}
