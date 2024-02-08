/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:45:15 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 15:49:00 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_heredoc(t_token *heredoc, int quotes,
	t_instance *ins, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HERE_MSG);
	while (line && ft_strncmp(heredoc->world, line, ft_strlen(heredoc->world))
		&& g_signal != STOP_HD)
	{
		if (quotes == 0)
			line = expander_heredoc(ins, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HERE_MSG);
	}
	free(line);
	if (g_signal == STOP_HD || !line)
		return (0);
	close(fd);
	return (1);
}

static int	heredoc(t_instance *ins, t_token *heredoc, char *file_name)
{
	int		quotes;
	int		res;

	res = 1;
	heredoc->world = check_heredoc_quotes(heredoc->world, &quotes);
	res = create_heredoc(heredoc, quotes, ins, file_name);
	g_signal = 0;
	ins->is_here = true;
	return (res);
}

int	check_fd_heredoc(t_instance *ins, int end[2], t_command *cmd)
{
	int	fd_in;

	if (ins->is_here)
	{
		close(end[0]);
		fd_in = open(cmd->here_doc, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

void	check_heredoc(t_instance *ins, t_command *cmd)
{
	t_token	*save;

	save = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->type == HERE)
		{
			if (cmd->here_doc)
				free(cmd->here_doc);
			cmd->here_doc = generate_heredoc_filename();
			if (heredoc(ins, cmd->redirections, cmd->here_doc) == 0)
			{
				ins->err_num = 1;
				reset_minishell(ins);
				return ;
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = save;
}
