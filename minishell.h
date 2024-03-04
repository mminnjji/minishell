/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:59:51 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/18 19:56:30 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line.h"
# include <sys/wait.h>
# include <termios.h>

int	g_exit_code;

typedef struct s_cmd
{
	char			**cmd;
	char			*init_cmd;
	int				infile;
	int				outfile;
	int				idx;
	int				heredoc_flag;
	struct s_cmd	*next;
	char			*cmd_path;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	execute(t_cmd *cmd, char ***env);
void	exec_cmd(t_cmd *curr, int pipefd[2], t_env *envs);
int		builtin(t_cmd *cmd, int pipefd[2], t_env **envs, int flag);
int		ft_env(t_cmd *cmd, t_env *envs, int pipefd[2], int flag);
int		ft_unset(t_cmd *cmd, t_env **envs);
int		ft_export(t_cmd *cmd, t_env **envs, int pipefd[2]);
int		ft_pwd(t_cmd *cmd, int pipefd[2]);
int		ft_cd(t_cmd *cmd, t_env *envs, char *tmp);
int		ft_echo(t_cmd *cmd, int pipefd[2], int flag);
int		ft_exit(t_cmd *cmd);
int		is_n(char *option);
void	find_path1(char **env, t_cmd *cmd);
void	find_path2(t_cmd *cmd, char **paths);
char	*addpath(char *only_cmd, int j, char **paths);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2, int i, int flag);
int		ft_error(t_cmd *cmd, char *message, int code, int ret);
void	ft_free(char ***arr);
int		ft_strchr(const char *s, char ch);
char	**d_strdup(char **s, int z);
char	*ft_strdup(char *s, int l);
int		ft_atoi(const char *nptr, int flag, int p, int answer);
void	sort(char **env);
void	ft_lstclear(t_env **lst);
int		same_key(char *cmd, t_env *curr);
void	check_export(char **cmd, int i, int j);
void	delete_envs(char *cmd, t_env **envs, t_env *for_curr, char *c_key);
char	*key(char *env);
char	*val(char *env);
char	**change_env(t_env *envs, int flag, t_env *curr, int len);
t_env	*make_envs(char **env, t_env *envs);
int		ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *key, char *val, char *check);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlen(char *s);
char	*find_key(t_env *envs, char *key);
void	cmd_error(t_cmd *curr);
t_cmd	*init_node(int idx);
char	**ft_split2(char const *str, char c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		parse_by_pipe(char *str, t_cmd **start, int pipe_n);
int		get_malloc_list(char *str, t_cmd **start);
int		parse_by_space(t_cmd **start);
int		parse_by_quote(t_cmd **start, int flag[]);
int		count_char(char *str, char c);
int		count_str(char *str, char c);
int		ft_strncmp2(char *s1, char *s2, size_t n);
char	*delete_char(char **str, int i, int n, int flag);
int		here_doc(t_cmd **tmp, int flag[], char *name);
char	*get_heredoc(t_cmd *tmp, int n, int *len, int flag[]);
int		check_heredoc(t_cmd **start, int flag[]);
int		check_redirect(t_cmd **start, char **envp);
char	*replace_env(char **str, int j, char **envp, int idx);
char	*ft_itoa(int n);
int		check_envp(t_cmd **start, char **envp);
char	*append_str2(char **str, int i, char *tmp);
int		minishell_free(t_cmd **start, int flag);
int		print_error(void);
int		r_heredoc(t_cmd **tmp, char *str, char *name, char **envp);
char	*change_str(t_cmd **tmp, int flag[], int i, char **envp);
void	ft_putstr_fd(char *s, int fd);
int		init_error(t_cmd *tmp);
char	*remove_quote(char *str);
char	**ft_freee(char **str);
int		ft_strncmp2(char *s1, char *s2, size_t n);
char	*delete_char(char **str, int i, int n, int flag);
char	*append_str(char **str, int i, char *tmp);
char	*append_str2(char **str, int i, char *tmp);
char	*get_path_q(int idx);
int		do_redirect_in(t_cmd **tmp, int i, char **envp);
int		do_redirect_out(t_cmd **tmp, int i, char **envp);
int		do_redirect_pout(t_cmd **tmp, int i, char **envp);
int		do_redirect_heredoc(t_cmd **tmp, int i, char *name, char **envp);
int		check_predirect(t_cmd **tmp, int flag[], char **envp);
void	check_flag(char *str, int flag[], int i);
int		make_pipe(int *pip, char *str, int pipe_n, int flag[]);
int		remove_env(char **str, char **envp, int idx, int f);
void	signal_cmd(int signum);
int		check_redirect_err(int err, int flag[]);
void	print_signal_off(void);
void	print_signal_on(void);
void	signal_check(int flag);
void	signal_heredoc_cmd(int signum);
void	signal_dfl(int signum);
void	signal_dfl2(int signum);
void	check_fork_signal(void);
int		cd_error(char old[1024], char new[1024], t_env *envs);

#endif
