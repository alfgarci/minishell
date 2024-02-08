/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:45:31 by alfgarci          #+#    #+#             */
/*   Updated: 2024/01/31 00:15:07 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_append_outfile(t_token *redirections)
{
	int	fd;

	if (redirections->type == APPEND)
		fd = open(redirections->world, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections->world, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

static int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

static int	handle_outfile(t_token *redirection)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	check_redirections(t_command *cmd)
{
	t_token	*save;

	save = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->type == LESS)
		{
			if (handle_infile(cmd->redirections->world))
				return (1);
		}
		else if (cmd->redirections->type == MORE
			|| cmd->redirections->type == APPEND)
		{
			if (handle_outfile(cmd->redirections))
				return (1);
		}
		else if (cmd->redirections->type == HERE)
		{
			if (handle_infile(cmd->here_doc))
				return (1);
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = save;
	return (0);
}
