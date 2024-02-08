/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:44:32 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 16:00:03 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_wait(t_instance *ins)
{
	int	i;
	int	status;

	i = -1;
	while (++i < ins->num_pipes)
		waitpid(ins->pid[i], &status, 0);
	waitpid(ins->pid[i], &status, 0);
	if (WIFEXITED(status))
		ins->err_num = WEXITSTATUS(status);
}

void	dup_pipe(t_command *cmd, t_instance *ins, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		minishell_error(PIPE_ERROR, ins);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		minishell_error(PIPE_ERROR, ins);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	run_cmd(cmd, ins);
}
