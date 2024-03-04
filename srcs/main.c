/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:14:49 by man               #+#    #+#             */
/*   Updated: 2023/12/22 11:19:53 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	work_cmd(char *str, char ***envp)
{
	t_cmd	*start;
	int		pipe_count;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	start = init_node(0);
	if (!start)
		return (print_error());
	pipe_count = get_malloc_list(str, &start);
	if (pipe_count < 0)
		return (minishell_free(&start, 0));
	if (parse_by_pipe(str, &start, pipe_count))
		return (minishell_free(&start, 0));
	if (check_redirect(&start, *envp))
		return (minishell_free(&start, 0));
	if (check_envp(&start, *envp))
		return (minishell_free(&start, 1));
	if (parse_by_space(&start))
		return (minishell_free(&start, 1));
	if (parse_by_quote(&start, flag))
		return (minishell_free(&start, 1));
	execute(start, envp);
	minishell_free(&start, 0);
	return (0);
}

void	print_start(void)
{
	printf("\033[38;5;49m%s\033[0m\n", \
	"┌────────────────────────────────────────────────┐");
	printf("\033[38;5;50m%s\033[0m\n", \
	"│                ╦ ╦╔═╗╦  ╦  ╔═╗┬                │");
	printf("\033[38;5;86m%s\033[0m\n", \
	"│                ╠═╣║╣ ║  ║  ║ ║│                │");
	printf("\033[38;5;122m%s\033[0m\n", \
	"│                ╩ ╩╚═╝╩═╝╩═╝╚═╝o                │");
	printf("\033[38;5;158m%s\033[0m\n", \
	"│             ╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦              │");
	printf("\033[38;5;158m%s\033[0m\n", \
	"│             ║║║║║║║║╚═╗╠═╣║╣ ║  ║              │");
	printf("\033[38;5;194m%s\033[0m\n", \
	"│             ╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝            │");
	printf("\033[38;5;230m%s               \033[0m%s\033\
[38;5;230m                %s\033[0m\n", "│", "by jiheekan & man", "│");
	printf("\033[38;5;230m%s\033[0m\n", \
	"└────────────────────────────────────────────────┘");
}

char	**start_main(int argc, char **argv)
{
	g_exit_code = 0;
	(void)argv;
	(void)argc;
	print_start();
	return (NULL);
}

int	set_myenv_str(char **envp, char ***myenv, char **str)
{
	signal_check(1);
	(*str) = readline("\033[38;5;122m""⋆ minishell ⋆ *･ﾟ✧""\033[0m"" ");
	if (!(*myenv))
		(*myenv) = d_strdup(envp, -1);
	if (!(*myenv))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	char	*str;
	char	**myenv;

	myenv = start_main(argc, argv);
	while (1)
	{
		if (set_myenv_str(envp, &myenv, &str))
			continue ;
		if (str)
		{
			if (!str[0])
				ft_free2((void **)&str);
			if (!str)
				continue ;
			work_cmd(str, &myenv);
			if (!myenv)
				g_exit_code = 1;
		}
		else
			break ;
		add_history(str);
		ft_free2((void **)&str);
	}
	ft_free(&myenv);
	return (0);
}
