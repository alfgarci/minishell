/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:53:34 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/07 02:07:01 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char	*cmd)
{
	if (is_str_indetical(cmd, "echo")
		|| is_str_indetical(cmd, "cd")
		|| is_str_indetical(cmd, "pwd")
		|| is_str_indetical(cmd, "export")
		|| is_str_indetical(cmd, "unset")
		|| is_str_indetical(cmd, "env")
		|| is_str_indetical(cmd, "exit"))
		return (1);
	else
		return (0);
}

t_command	*new_command(char **args, t_token *red)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = args;
	if (args[0])
		new->is_builtin = is_builtin(args[0]);
	else
		new->is_builtin = 0;
	new->here_doc = NULL;
	new->redirections = red;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	command_add_back(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*tmp;

	tmp = *cmd_list;
	if (*cmd_list == NULL)
	{
		*cmd_list = new_cmd;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
	new_cmd->prev = tmp;
}
