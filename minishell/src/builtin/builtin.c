/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:42:24 by alfgarci          #+#    #+#             */
/*   Updated: 2024/01/31 00:30:53 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(t_instance *ins, t_command *cmd)
{
	int	ret;

	ret = 0;
	if (is_str_indetical(cmd->args[0], "echo"))
		ret = my_echo(cmd);
	else if (is_str_indetical(cmd->args[0], "env"))
		ret = env(ins, cmd);
	else if (is_str_indetical(cmd->args[0], "unset"))
		ret = unset(ins, cmd);
	else if (is_str_indetical(cmd->args[0], "export"))
		ret = export(ins, cmd);
	else if (is_str_indetical(cmd->args[0], "pwd"))
		ret = pwd(ins);
	else if (is_str_indetical(cmd->args[0], "cd"))
		ret = cd(ins, cmd);
	else if (is_str_indetical(cmd->args[0], "exit"))
	{
		my_exit(ins, cmd);
		return (0);
	}
	return (ret);
}
