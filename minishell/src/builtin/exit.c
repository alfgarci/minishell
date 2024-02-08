/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:17:19 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	int	i;
	int	is_num;

	i = -1;
	is_num = 1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			is_num = 0;
			break ;
		}
	}
	return (is_num);
}

static int	get_err_code(int err)
{
	int	final_code;

	final_code = err;
	if (final_code > 255)
		final_code = final_code % 256;
	return (final_code);
}

void	my_exit(t_instance *ins, t_command *cmd)
{
	int	err_code;

	err_code = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd->args[1])
		err_code = ins->err_num;
	else if (!is_num(cmd->args[1]))
		err_code = exit_error(cmd->args[1]);
	else if (cmd->args[1] && !cmd->args[2])
	{
		if (is_num(cmd->args[1]))
			err_code = get_err_code(atoi(cmd->args[1]));
		else
			err_code = exit_error(cmd->args[1]);
	}
	else if (is_num(cmd->args[1]) && cmd->args[2])
		minishell_error(EXIT_ERROR, ins);
	else if (!is_num(cmd->args[2]))
		err_code = exit_error(cmd->args[1]);
	end_minishell(ins, err_code);
}
