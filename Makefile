CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = execute/execute.c execute/builtin1.c execute/builtin2.c execute/path.c execute/add.c execute/split.c \
execute/envs1.c execute/envs2.c execute/envs3.c srcs/main.c srcs/env.c parse/ft_itoa.c parse/ft_split.c srcs/init.c\
parse/parse.c srcs/util.c  heredoc/get_next_line_util.c heredoc/get_next_line.c \
heredoc/heredoc.c heredoc/redirection.c signal/signal.c heredoc/error.c srcs/env_util.c \
heredoc/heredoc_util.c heredoc/redirection_util.c execute/d_arr.c signal/signal_util.c execute/exec_errors.c execute/builtin3.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
