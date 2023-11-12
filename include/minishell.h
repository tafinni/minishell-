/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:40:57 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/13 13:26:05 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>

# define FAIL 1
# define SUCCESS 0

// commands
# define ECHO_CMD 1
# define CD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6
# define PWD 7

// redirection
# define L_ONE 1 // <
# define L_TWO 2 // <<
# define R_ONE 3 // >
# define R_TWO 4 // >>

//cmds
# define CMD 1
# define ARG 2

//FILE
# define INFILE 1
# define OUTFILE 2
# define APPEND 3

// Global variable to return in 'echo $?'
extern int	g_ret_number;

typedef struct s_args
{
	char			*str;
	int				quote;
	int				redir;
	int				pipe;
	int				expand;
	int				counter;
	struct s_args	*next;
}	t_args;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int				cmd_id;
	char			*cmd_str;
	char			**str;
	char			**redir_to;
	int				*file;
	int				order;
	int				infiles;
	int				outfiles;
	int				str_len;
	int				in;
	int				out;
	int				error;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	char	*str;
	int		prev_redir;
	char	*input;
	int		args_len;
	int		tokens_len;
	char	**env_arr;
	int		error;
	int		heredoc_sign;
	int		redir_parser_check;
	int		found_command;
	int		prev_pipe;
	t_env	*env;
	t_token	*start_tokens;
	t_args	*args;
}	t_data;

// builtins - functions
void	builtin_echo(t_data *data, char **args, int index);
void	builtin_pwd(void);
void	builtin_cd(char **arg, t_env *env_list);
void	builtin_env(t_env *env_list, char **argv);
void	builtin_exit(t_data *data, char **args);
void	builtin_unset(char **arg, t_env **env_list);
void	builtin_export(t_data *data, char **arg, t_env **env_list);
int		check_envvar_name_export(char *str);
int		builtins(t_data *data, t_token *token, t_env *env_list);

// env - functions
void	init_env(char **env, t_env **env_list);
int		find_replace_env(char *find_str, char *replace_str, 
			t_env **env_list, int non_value);
char	*get_environment(char *find_name, t_env *env_list);
t_env	**add_to_back_env(t_env **list, t_env *new);
char	**ft_split_env(t_data *data, char const *s, char c);
char	*expand_variables_and_replace(t_data *data, char *str);

//executer/env_path_utils - functions
void	saved_to_res(t_data *data, char **res, int i, char **saved);
char	*found_path(char **to_check, char *res);
t_env	*search_env_for_path(t_env *env);

// executer/env_path - functions
char	*find_path(t_data *data, t_env *env, char *check_str, int i);
char	**get_env_arr(t_data *data, int i);

// executer/executer_utils - functions
void	waitprocesses(t_data *data, int *process);
int		create_processes(t_data *data, int *process, int position);
int		one_builtin(t_data *data, t_token *temp, int in, int out);
void	handle_end(t_data *data, t_token *temp);
void	dup_and_close(t_token *temp, int *in, int *out, int flag);

// executer/executer - functions
int		run_list(t_data *data, t_token *tokens, int position, int *process);

// executer/input_output - functions
int		get_output_input(t_data *data, t_token *temp, int p, int *fd);
void	set_in_out(t_token *temp);

// expand - functions
void	expand_args(t_data *data, t_args *arg_list);
char	**split_replace(t_data *data, char **tmp_split_str, int *index, 
			char *tmp_str);
char	*join_strings(t_data *data, char **string_array, int array_length);
void	expand_handle_multiquote(t_data *data, t_args *args,
			int *i, char quote_char);
char	*expand_variables_and_replace(t_data *data, char *str);

// lexer/handle_quotes - functions
int		check_redir_quote(t_data *data, t_args *node, int i, int *len);

// lexer/lexer_utils - functions
void	set_arg_node(t_args *node);
int		check_space(char c);
t_args	*add_to_back_args(t_args *list, t_args *new);
t_args	*lexer_error(t_data *data, t_args *args, t_args *node);
void	lexer_msg(char token);

// lexer/lexer - functions
t_args	*str_to_arg_list(t_data *data, char *input, t_args *arg_list, int i);
int		count_redir(t_args *node, char *input, int *len, int i);
int		check_quote(char *input, int i, int *len);

// lexer/node_str - functions
char	*ft_node_str(t_data *data, char *input, int start, int len);
char	*get_redir_str(t_args *node);

// lexer/redir_pipe_utils - functions
int		redir_not_first(t_data *data, int *len, int i);
int		redir_first(t_data *data, t_args *node, int *len, int i);
int		pipe_first_or_not(t_data *data, t_args *node, int i, int flag);

// parser/handle_redir - functions
int		has_redir(t_data *data, t_token *new, t_args *temp, int i);
void	str_redir_check(t_data *data, t_token *new, t_args *temp, int *cmds);
int		redir_parser_check(t_args *temp);

// parser/heredoc
void	get_heredoc(t_data *data, t_token *new, t_args *temp, int i);

// parser/parser_utils - functions
void	set_token(t_token *new);
int		compare_str(char *str1, char *str2);
int		cmd_id(t_token *new);
t_token	*add_to_back_token(t_token *list, t_token *new);
int		parser_error(t_args *args, t_token *tokens, t_token *node);

// parser - functions
int		get_tokens(t_data *data, t_token *tokens,
			t_args *args, int first_count);
int		get_token_args(t_data *data, t_args *temp, t_token *new, int cmds);

// parser/str_handler - functions
void	first_found_command(t_data *data, t_args *temp, t_token *new);
void	first_str(t_data *data, t_args *temp, t_token *new);
void	add_to_str(t_data *data, t_args *temp, t_token *new, int cmds);
void	move_str(t_token **token);
void	new_cmd_str(t_token **token);

// signal - functions
void	ctrl_d(void);
void	set_signals(void);
void	set_signal_child(void);
void	close_echoctl(struct termios *t);
void	reset_echoctl(struct termios *t);
void	handle_signal_heredoc(int sig);

// free - functions
void	free_tokens(t_token **token);
void	free_args(t_args **args);
void	free_env_list(t_env **env_list);
void	free_prompt(char *input, t_data *data);

// free_utils
void	free_str(char *str);
void	free_2d_str(char **str);

// str_checker - functions
int		check_arg_errors(t_args *args);

// utils - functions
void	ft_error(t_data *data, char *str, int flag);
int		args_len(t_args *args);
int		redir_error(t_args *temp);
int		cmd_str_check(t_token *temp);

#endif
