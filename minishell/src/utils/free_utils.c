/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:52:34 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/06 21:56:20 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token	**token_list)
{
	t_token	*tmp;

	if (*token_list)
	{
		while (*token_list)
		{
			tmp = (*token_list)->next;
			if ((*token_list)->world)
				free((*token_list)->world);
			free(*token_list);
			*token_list = tmp;
		}
		*token_list = NULL;
	}
}

void	free_cmds(t_command **cmd_list)
{
	t_command	*tmp;
	t_token		*red_tmp;

	if (!*cmd_list)
		return ;
	while (*cmd_list)
	{
		tmp = (*cmd_list)->next;
		red_tmp = (*cmd_list)->redirections;
		free_tokens(&red_tmp);
		if ((*cmd_list)->args)
			free_split((*cmd_list)->args);
		if ((*cmd_list)->here_doc)
			free((*cmd_list)->here_doc);
		free(*cmd_list);
		*cmd_list = tmp;
	}
	*cmd_list = NULL;
}

void	free_split(char **split)
{
	int	aux;

	aux = -1;
	while (*(split + ++aux))
		free(*(split + aux));
	free(split);
}

int	end_minishell(t_instance *ins, int err_code)
{
	free_split(ins->paths);
	free_split(ins->envp);
	free(ins->prompt);
	if (ins->home)
		free(ins->home);
	if (ins->old_pwd)
		free(ins->old_pwd);
	if (ins->pwd)
		free(ins->pwd);
	free_cmds(&ins->cmd_list);
	if (ins->token_list)
		free_tokens(&ins->token_list);
	if (ins->list_parser)
		free_tokens(&ins->list_parser);
	if (ins->list_red_parser)
		free_tokens(&ins->list_red_parser);
	if (ins->num_pipes > 0)
		free(ins->pid);
	exit(err_code);
}
