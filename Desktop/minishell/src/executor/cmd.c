/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:44:24 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 15:59:59 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_execve(t_command *cmd, t_instance *ins)
{
	int		i;
	char	*path_cmd;

	i = -1;
	if (!access(cmd->args[0], F_OK))
		execve(cmd->args[0], cmd->args, ins->envp);
	while (ins->paths[++i])
	{
		path_cmd = ft_strjoin(ins->paths[i], cmd->args[0]);
		if (!access(path_cmd, F_OK))
			execve(path_cmd, cmd->args, ins->envp);
		free(path_cmd);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putendl_fd(CMD_NOT_FOUNF, STDERR_FILENO);
	return (127);
}

void	run_cmd(t_command *cmd, t_instance *ins)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	if (cmd->is_builtin == 1)
	{
		exit_code = builtin(ins, cmd);
		exit(exit_code);
	}
	else if (cmd->args[0][0] != '\0')
		exit_code = run_execve(cmd, ins);
	exit(exit_code);
}
