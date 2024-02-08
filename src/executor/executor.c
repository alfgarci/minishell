/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:44:45 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 15:58:07 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*get_first_cmd(t_command *cmd_list)
{
	if (!cmd_list)
		return (NULL);
	while (cmd_list->prev != NULL)
		cmd_list = cmd_list->prev;
	return (cmd_list);
}

static int	do_fork(t_instance *ins, int end[2], int fd_in, t_command *cmd)
{
	static int	i = 0;

	if (ins->reset == true)
	{
		i = 0;
		ins->reset = false;
	}
	ins->pid[i] = fork();
	if (ins->pid[i] < 0)
		minishell_error(FORK_ERROR, ins);
	if (ins->pid[i] == 0)
		dup_pipe(cmd, ins, end, fd_in);
	i++;
	return (1);
}

static void	one_command(t_command *cmd, t_instance *ins)
{
	int	pid;
	int	status;

	if (cmd->is_builtin)
	{
		if (is_str_indetical(cmd->args[0], "cd")
			|| is_str_indetical(cmd->args[0], "exit")
			|| is_str_indetical(cmd->args[0], "export")
			|| is_str_indetical(cmd->args[0], "unset"))
		{
			ins->err_num = builtin(ins, cmd);
			return ;
		}
	}
	check_heredoc(ins, cmd);
	pid = fork();
	if (pid < 0)
		minishell_error(FORK_ERROR, ins);
	if (pid == 0)
		run_cmd(cmd, ins);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ins->err_num = WEXITSTATUS(status);
	else
		ins->err_num = ERR_CMD;
}

static void	do_pipe(t_instance	*ins)
{
	int	end[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (ins->cmd_list)
	{
		if (ins->cmd_list->next)
			pipe(end);
		check_heredoc(ins, ins->cmd_list);
		do_fork(ins, end, fd_in, ins->cmd_list);
		close(end[1]);
		if (ins->cmd_list->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(ins, end, ins->cmd_list);
		if (ins->cmd_list->next)
			ins->cmd_list = ins->cmd_list->next;
		else
			break ;
	}
	pipe_wait(ins);
	ins->cmd_list = get_first_cmd(ins->cmd_list);
}

void	executor(t_instance *ins)
{
	signal(SIGQUIT, sig_ctrl4);
	g_signal = IN_CMD;
	if (ins->num_pipes == 0)
		one_command(ins->cmd_list, ins);
	else
	{
		ins->pid = ft_calloc(sizeof(int), ins->num_pipes + 2);
		if (!ins->pid)
			minishell_error(MALLOC_ERROR, ins);
		do_pipe(ins);
	}
	g_signal = 0;
}
