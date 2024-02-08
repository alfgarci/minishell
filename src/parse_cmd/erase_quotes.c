/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:54:02 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/04 18:54:48 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*del_quotes(char *str, char quote)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	cnt;

	i = -1;
	cnt = 0;
	while (str[++i])
		if (str[i] != quote)
			cnt++;
	ret = ft_calloc(cnt + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != quote)
			ret[j++] = str[i];
	return (ret);
}

char	first_quote(char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			return (quote);
		}
	}
	return (quote);
}

void	erase_quotes(t_command *cmd_list)
{
	t_command	*cmd;
	int			i;
	char		*tmp;
	char		quote;

	cmd = cmd_list;
	while (cmd)
	{
		i = -1;
		while (cmd->args[++i])
		{
			quote = first_quote(cmd->args[i]);
			if (quote != 0)
			{
				tmp = cmd->args[i];
				cmd->args[i] = del_quotes(tmp, quote);
				free(tmp);
			}
		}
		cmd = cmd->next;
	}
}
