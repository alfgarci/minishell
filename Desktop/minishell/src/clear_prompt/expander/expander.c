/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:16:03 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_dollar_to_expand(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (str[0] == '\'')
		return (0);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		{
			count++;
		}
	}
	return (count);
}

static char	*search_value(t_instance *ins, char *var)
{
	int		i;
	char	**split;
	char	*value;

	i = -1;
	if (is_str_indetical(var, "?"))
	{
		free(var);
		return (ft_itoa(ins->err_num));
	}
	while (ins->envp[++i])
	{
		split = ft_split(ins->envp[i], '=');
		if (is_str_indetical(split[0], var))
		{
			value = ft_strdup(split[1]);
			free_split(split);
			free(var);
			return (value);
		}
		free_split(split);
	}
	free(var);
	return ("");
}

static char	*search_dollar_word(char *str)
{
	int		i;
	char	*word;

	i = -1;
	word = malloc(0);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != '$'
				&& (ft_isalnum(str[i]) || str[i] == '?' || str[i] == '_'))
			{
				word = add_char_str(word, str[i]);
				i++;
			}
			break ;
		}
	}
	return (word);
}

void	expander(t_instance *ins, char **arr)
{
	int		i;
	char	*front;
	char	*back;
	char	*key;
	int		num_dollar;

	i = -1;
	while (arr[++i])
	{
		num_dollar = count_dollar_to_expand(arr[i]);
		while (num_dollar > 0)
		{
			front = ft_substr(arr[i], 0, count_char_before(arr[i]));
			key = search_dollar_word(arr[i]);
			back = ft_substr(arr[i], ft_strlen(key) + ft_strlen(front) + 1,
					ft_strlen(arr[i]));
			key = search_value(ins, key);
			free(arr[i]);
			arr[i] = strjoin_3(front, key, back);
			free_expander(front, back, key);
			num_dollar--;
		}
	}
}

char	*expander_heredoc(t_instance *ins, char *line)
{
	char	*front;
	char	*back;
	char	*key;
	int		num_dollar;

	num_dollar = count_dollar_to_expand(line);
	while (num_dollar > 0)
	{
		front = ft_substr(line, 0, count_char_before(line));
		key = search_dollar_word(line);
		back = ft_substr(line, ft_strlen(key) + ft_strlen(front) + 1,
				ft_strlen(line));
		key = search_value(ins, key);
		free(line);
		line = strjoin_3(front, key, back);
		free_expander(front, back, key);
		num_dollar--;
	}
	return (line);
}
