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

int	ft_pwd(t_cmd *cmd, int pipefd[2])
{
	char	arr[1024];

	if (cmd->outfile == 1 && cmd->next)
		cmd->outfile = pipefd[1];
	if (getcwd(arr, sizeof(arr)) != 0)
	{
		write(cmd->outfile, arr, ft_strlen(arr));
		write(cmd->outfile, "\n", 1);
	}
	else
		ft_error(0, 0, 1, 0);
	return (1);
}
