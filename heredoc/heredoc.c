/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:28:38 by man               #+#    #+#             */
/*   Updated: 2023/12/22 13:00:55 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	break_line(t_cmd **tmp, char *name, int file, char *str)
{
	char	*t_path;

	t_path = ttyname(STDOUT_FILENO);
	open(t_path, O_RDONLY);
	(*tmp)->infile = open(name, O_RDONLY);
	unlink(name);
	ft_free2((void **)&str);
	ft_free2((void **)&name);
	close(file);
	return (0);
}

int	return_heredoc(int file, t_cmd **tmp, char **name, char **str)
{
	(*tmp)->infile = open(*name, O_RDONLY);
	if ((*tmp)->infile < 0)
		return (2);
	unlink(*name);
	ft_free2((void **)str);
	ft_free2((void **)name);
	close(file);
	return (0);
}

int	r_heredoc(t_cmd **tmp, char *str, char *name, char **envp)
{
	int		file;
	char	*line;

	file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (2);
	signal_check(3);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			return (break_line(tmp, name, file, str));
		if (!ft_strncmp2(str, line, ft_strlen(str)) \
		&& ft_strlen(str) == (ft_strlen(line) - 1))
			break ;
		if (!(*tmp)->heredoc_flag)
			if (remove_env(&line, envp, (*tmp)->idx, 1))
				return (1);
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (return_heredoc(file, tmp, &name, &str));
}

char	*change_str(t_cmd **tmp, int flag[], int i, char **envp)
{
	char	*str;
	int		qflag[2];

	qflag[0] = 0;
	qflag[1] = 0;
	str = get_heredoc(*tmp, i + flag[0], &flag[0], qflag);
	if (!str)
		return (NULL);
	if (flag[1])
	{
		if (remove_env(&str, envp, (*tmp)->idx, 0))
			return (NULL);
	}
	str = remove_quote(str);
	if (!str)
		return (NULL);
	(*tmp)->init_cmd = delete_char(&((*tmp)->init_cmd), i, flag[0], 0);
	if (!(*tmp)->init_cmd)
		return (NULL);
	return (str);
}
