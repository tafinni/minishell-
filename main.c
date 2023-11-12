/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:36:07 by akuzmenk          #+#    #+#             */
/*   Updated: 2023/09/13 14:11:11 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_ret_number = 0;

int	args_checker(t_args *args)
{
	if (args->next == NULL && ft_strlen(args->str) < 1 && args->redir == 0)
		return (1);
	else
		return (0);
}

void	set_data(t_data *data, char *input)
{
	data->args_len = 0;
	data->prev_pipe = 0;
	data->prev_redir = 0;
	data->input = input;
	data->env_arr = NULL;
	data->error = 0;
}

int	check_string(char *input, t_data *data, t_token *token_list)
{
	t_args	*arg_list; 

	arg_list = NULL;
	set_data(data, input);
	arg_list = str_to_arg_list(data, input, arg_list, 0);
	if (arg_list == NULL || !arg_list || args_checker(arg_list) == 1)
		return (1);
	if (check_arg_errors(arg_list) == -1)
	{
		g_ret_number = 258;
		free_args(&arg_list);
		data->start_tokens = NULL;
		data->tokens_len = 0;
		return (1);
	}
	data->args = arg_list;
	expand_args(data, arg_list);
	data->error = 0;
	if (arg_list != NULL)
	{
		if (get_tokens(data, token_list, arg_list, 0) == 1)
			return (1);
	}
	return (0);
}

void	create_prompt(char *input, t_data *data, char **envp)
{
	t_env			*env_list;
	t_token			*token_list;
	struct termios	t;

	env_list = NULL;
	token_list = NULL;
	init_env(envp, &env_list);
	data->env = env_list;
	tcgetattr(0, &t);
	while (1)
	{
		set_signals();
		close_echoctl(&t);
		input = readline("\033[0;34mminishell$ \033[0m");
		reset_echoctl(&t);
		if (!input)
			ctrl_d();
		if (ft_strlen(input) > 0)
			add_history(input);
		if (check_string(input, data, token_list) == 0)
			run_list(data, data->start_tokens, -1, 0);
		free_prompt(input, data);
	}
	free_env_list(&env_list);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	data;

	input = NULL;
	if (argc == 1 && argv)
		create_prompt(input, &data, envp);
	return (g_ret_number);
}
