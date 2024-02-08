/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:52:34 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/04 15:59:26 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipe_errors(t_instance *ins, t_token *token_list)
{
	if (!ins->token_list)
		parse_error(ins, NULL);
	if (token_list->type == PIPE)
		parse_error(ins, token_list);
}

void	check_fist_tokken(t_instance *ins)
{
	if (ins->token_list->type == PIPE)
		parse_error(ins, ins->token_list);
}

void	check_redirections_syntax_error(t_instance *ins, t_token *token)
{
	if (!token->next)
		parse_error(ins, token);
	if (token->next->type != 0)
		parse_error(ins, token->next);
}

void	parse_error(t_instance *ins, t_token *token)
{
	ft_putstr_fd(PARSE_ERROR, STDERR_FILENO);
	if (token == NULL)
		ft_putendl_fd("\'\\n\'", STDERR_FILENO);
	else if (token->type == PIPE)
		ft_putendl_fd("'|'", STDERR_FILENO);
	else if (token->type == LESS)
		ft_putendl_fd("'<'", STDERR_FILENO);
	else if (token->type == MORE)
		ft_putendl_fd("'>'", STDERR_FILENO);
	else if (token->type == HERE)
		ft_putendl_fd("'<<'", STDERR_FILENO);
	else if (token->type == APPEND)
		ft_putendl_fd("'>>'", STDERR_FILENO);
	else
	{
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(token->world, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ins->err_num = 1;
	reset_minishell(ins);
}
