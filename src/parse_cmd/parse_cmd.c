/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:54:11 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/07 02:05:10 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*make_command_list(t_instance *ins)
{
	int			i;
	char		**args;
	int			size;
	t_token		*tmp;
	t_command	*new_cmd;

	i = 0;
	search_redirections(ins, 0);
	size = count_args(ins->list_parser);
	args = ft_calloc(size + 1, sizeof(char *));
	if (!args)
		minishell_error(MALLOC_ERROR, ins);
	tmp = ins->list_parser;
	while (size > 0)
	{
		if (tmp->world)
		{
			args[i++] = ft_strdup(tmp->world);
			delete_i_token(&ins->list_parser, tmp->num);
			tmp = ins->list_parser;
		}
		size--;
	}
	new_cmd = new_command(args, ins->list_red_parser);
	return (new_cmd);
}

void	parse_cmd(t_instance *ins)
{
	t_command	*new_cmd;

	if (!ins->token_list)
		reset_minishell(ins);
	count_pipes(ins);
	check_fist_tokken(ins);
	while (ins->token_list)
	{
		if (ins->token_list && ins->token_list->type == PIPE)
			delete_i_token(&ins->token_list, ins->token_list->num);
		check_pipe_errors(ins, ins->token_list);
		ins->list_parser = ins->token_list;
		ins->list_red_parser = NULL;
		new_cmd = make_command_list(ins);
		if (!new_cmd)
			minishell_error(MALLOC_ERROR, ins);
		if (!ins->cmd_list)
			ins->cmd_list = new_cmd;
		else
			command_add_back(&ins->cmd_list, new_cmd);
		ins->token_list = ins->list_parser;
	}
	erase_quotes(ins->cmd_list);
}
