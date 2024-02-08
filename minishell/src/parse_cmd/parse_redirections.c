/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:54:34 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/07 02:06:55 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(int type)
{
	if (type == 60 || type == 62 || type == 388 || type == 488)
		return (1);
	else
		return (0);
}

void	new_redirection(t_instance *ins, t_token *token, int i)
{
	t_token	*new;
	int		pos_red;
	int		pos_file;

	new = new_token(ft_strdup(token->next->world), token->type, i);
	if (!new)
		minishell_error(MALLOC_ERROR, ins);
	token_add_back(&ins->list_red_parser, new);
	pos_red = token->num;
	pos_file = token->next->num;
	delete_i_token(&ins->list_parser, pos_red);
	delete_i_token(&ins->list_parser, pos_file);
}

void	search_redirections(t_instance *ins, int i)
{
	t_token	*tmp;

	tmp = ins->list_parser;
	while (tmp && tmp->type == 0)
		tmp = tmp->next;
	if (!tmp || tmp->type == PIPE)
		return ;
	else
	{
		check_redirections_syntax_error(ins, tmp);
		if (is_redirection(tmp->type))
			new_redirection(ins, tmp, i);
		search_redirections(ins, i + 1);
	}
}
