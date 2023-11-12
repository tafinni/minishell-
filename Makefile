# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 13:36:16 by akuzmenk          #+#    #+#              #
#    Updated: 2023/09/13 13:20:34 by tfinni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
INC = ./include
FLAGS := -Wall -Wextra -Werror #-g -fsanitize=address
LIBS := -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline

LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

SRCS :=	\
	main.c \
	builtins/builtin_echo.c \
	builtins/builtin_pwd.c \
	builtins/builtin_env.c \
	builtins/builtin_cd.c \
	builtins/builtin_export.c \
	builtins/builtin_export_utils.c \
	builtins/builtin_exit.c \
	builtins/builtin_unset.c \
	lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/handle_quotes.c \
	lexer/node_str.c \
	lexer/redir_pipe_utils.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/handle_redir.c \
	parser/str_handler.c \
	parser/heredoc.c \
	executer/executer.c \
	executer/executer_utils.c \
	executer/input_output.c \
	executer/env_path.c \
	executer/env_path_utils.c \
	env/environment_functions.c \
	env/ft_split_env.c \
	utils.c \
	str_checker.c \
	free_function.c \
	free_utils.c \
	signal/signal.c \
	signal/signal_echoctl.c \
	signal/signal_heredoc.c \
	builtins/builtins.c \
	expand/expand_functions.c \
	expand/expand_handle_multiquote.c \
	expand/expand_functions_utils.c 

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -sC $(LIBFT_DIR)
	cc $(FLAGS) $(OBJS) -o $(NAME) $(LIBS) -L. $(LIBFT_LIB)

%.o: %.c
	cc $(FLAGS) -I ~/.brew/opt/readline/include -I $(INC) -c $< -o $@

clean:
	make clean -sC $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -sC $(LIBFT_DIR)
	rm -f $(NAME)
	
re: fclean all

.PHONY: clean fclean re
