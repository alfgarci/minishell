/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:15:32 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char_before(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '?' || str[i + 1] == '_'))
			break ;
	}
	return (i);
}

char	*add_char_str(char *str, char c)
{
	int		i;
	char	*new;

	i = -1;
	new = (char *)malloc((ft_strlen(str) + 2) * sizeof(char));
	while (str[++i])
		new[i] = str[i];
	new[i++] = c;
	new[i] = '\0';
	free(str);
	return (new);
}

void	free_expander(char *front, char *back, char *key)
{
	free(front);
	free(back);
	if (!is_str_indetical(key, ""))
		free(key);
}
