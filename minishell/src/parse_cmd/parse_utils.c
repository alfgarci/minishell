/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:54:49 by alfgarci          #+#    #+#             */
/*   Updated: 2024/01/30 22:31:24 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_instance *ins)
{
	t_token	*tmp;

	tmp = ins->token_list;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			ins->num_pipes++;
		tmp = tmp->next;
	}
}

int	count_args(t_token *list_parser)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = list_parser;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->num >= 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
