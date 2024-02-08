/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:16:53 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*jump_special_char(char *str, int index)
{
	if ((str[index] == str[index + 1]) && str[index] == '>')
	{
		return (ft_strdup(">>"));
	}
	else if (((str[index] == str[index + 1]) && str[index] == '<'))
	{
		return (ft_strdup("<<"));
	}
	else if (str[index] == '<')
		return (ft_strdup("<"));
	else if (str[index] == '>')
		return (ft_strdup(">"));
	else
		return (ft_strdup("|"));
}

static char	*jump_word(char *str, int index)
{
	int		save_index;
	char	*word;
	int		in_quote;
	char	quote;

	save_index = index;
	in_quote = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\'' || str[index] == '\"')
		{
			if (in_quote && quote == str[index])
				in_quote = !in_quote;
			else
			{
				quote = str[index];
				in_quote = 1;
			}
		}
		if ((is_special_char(str[index]) || is_space(str[index])) && !in_quote)
			break ;
		index++;
	}
	word = strndup(str + save_index, (index - save_index));
	return (word);
}

int	count_words(char *str)
{
	int		i;
	char	*word;
	int		count;

	i = 0;
	count = 0;
	word = NULL;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (is_special_char(str[i]))
			word = jump_special_char(str, i);
		else
			word = jump_word(str, i);
		count++;
		i += ft_strlen(word);
		free(word);
	}
	return (count);
}

char	**split_prompt(char *str, int count)
{
	char	**words;
	int		i;
	int		num_word;
	char	*word;

	words = calloc(count + 1, sizeof(char *));
	i = 0;
	word = NULL;
	num_word = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (is_special_char(str[i]))
			word = jump_special_char(str, i);
		else
			word = jump_word(str, i);
		words[num_word++] = word;
		i += ft_strlen(word);
	}
	return (words);
}
