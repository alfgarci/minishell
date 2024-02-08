/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:17:06 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_token(char *world, int type, t_token **token_list, int i)
{
	t_token	*new;

	new = new_token(world, type, i);
	if (!new)
		return (0);
	token_add_back(token_list, new);
	return (1);
}

void	tokenizer(t_instance *ins, char **token_arr)
{
	int	i;

	i = -1;
	while (token_arr[++i])
	{
		if (*token_arr[i] == 0)
			continue ;
		if (ft_strncmp(token_arr[i], "<", ft_strlen(token_arr[i])) == 0)
			add_token(NULL, LESS, &ins->token_list, i);
		else if (ft_strncmp(token_arr[i], "<<", ft_strlen(token_arr[i])) == 0)
			add_token(NULL, HERE, &ins->token_list, i);
		else if (ft_strncmp(token_arr[i], ">", ft_strlen(token_arr[i])) == 0)
			add_token(NULL, MORE, &ins->token_list, i);
		else if (ft_strncmp(token_arr[i], ">>", ft_strlen(token_arr[i])) == 0)
			add_token(NULL, APPEND, &ins->token_list, i);
		else if (ft_strncmp(token_arr[i], "|", ft_strlen(token_arr[i])) == 0)
			add_token(NULL, PIPE, &ins->token_list, i);
		else
			add_token(token_arr[i], OTHER, &ins->token_list, i);
	}
}
