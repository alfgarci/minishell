/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:17:00 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **token_list, t_token *new)
{
	t_token	*tmp;

	tmp = *token_list;
	if (*token_list == NULL)
	{
		*token_list = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

t_token	*delete_token(t_token **token_list)
{
	if ((*token_list)->world)
	{
		free((*token_list)->world);
		(*token_list)->world = NULL;
	}
	free(*token_list);
	*token_list = NULL;
	return (NULL);
}

void	delete_fisrt_token(t_token **token_list)
{
	t_token	*tmp;

	tmp = *token_list;
	*token_list = tmp->next;
	delete_token(&tmp);
	if (*token_list)
		(*token_list)->prev = NULL;
}

void	delete_i_token(t_token **token_list, int key)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*start;

	start = *token_list;
	tmp = start;
	if ((*token_list)->num == key)
	{
		delete_fisrt_token(token_list);
		return ;
	}
	while (tmp && tmp->num != key)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
		prev->next = tmp->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	delete_token(&tmp);
	*token_list = start;
}

t_token	*new_token(char *world, int type, int i)
{
	t_token		*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->world = world;
	new->type = type;
	new->num = i;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
