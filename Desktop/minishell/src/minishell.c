/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:40:15 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/06 23:02:26 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_msg(t_instance *ins)
{
	char	**split_aux;
	char	*name;
	char	*tmp;

	if (is_str_indetical(ins->pwd, "/"))
		name = ft_strdup(ins->pwd);
	else
	{
		split_aux = ft_split(ins->pwd, '/');
		name = ft_strdup(split_aux[len_arr(split_aux) - 1]);
		free_split(split_aux);
	}
	tmp = strjoin_3("\033[0;96m", name, " \033[0m");
	free(name);
	if (ins->err_num == 0)
		name = ft_strjoin(GREEN_ARROW, tmp);
	else
		name = ft_strjoin(RED_ARROW, tmp);
	free(tmp);
	return (name);
}

void	reset_minishell(t_instance *ins)
{
	free_cmds(&ins->cmd_list);
	free(ins->prompt);
	if (ins->pid)
		free(ins->pid);
	free_split(ins->paths);
	init_rest_instance(ins);
	ins->reset = true;
	minishell(ins);
}

void	get_args(t_instance *ins)
{
	char	*tmp;
	char	*save;
	char	*prompt_msg;

	prompt_msg = get_prompt_msg(ins);
	ins->prompt = readline(prompt_msg);
	free(prompt_msg);
	if (!ins->prompt)
		ctrl_d(ins);
	if (ins->prompt[0] == '\0')
	{
		reset_minishell(ins);
		return ;
	}
	while (!are_quotes_closed(ins->prompt))
	{
		tmp = readline(QUOTE_MSG);
		if (!ins->prompt)
			minishell_error(RD_ERROR, ins);
		save = ins->prompt;
		ins->prompt = ft_strjoin(ins->prompt, tmp);
		free(save);
		free(tmp);
	}
	add_history(ins->prompt);
}

void	minishell(t_instance *ins)
{
	char	**token_arr;

	get_args(ins);
	token_arr = clean_prompt(ins);
	tokenizer(ins, token_arr);
	parse_cmd(ins);
	executor(ins);
	reset_minishell(ins);
}

int	main(int argc, char **argv, char **env)
{
	t_instance	ins;

	if (argc != 1 || argv[1])
	{
		printf("%s\n", ARGS_ERROR);
		exit(0);
	}
	init_signals();
	init_instance(&ins, env);
	minishell(&ins);
	return (0);
}
