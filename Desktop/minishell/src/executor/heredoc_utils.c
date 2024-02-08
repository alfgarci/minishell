/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:14:43 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 15:47:02 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_heredoc_quotes(char *delimiter, int *quotes)
{
	char	*new;

	*quotes = 0;
	new = delimiter;
	if (delimiter[0] == '\"' && delimiter[ft_strlen(delimiter) - 1] == '\"')
	{
		*quotes = 1;
		new = ft_strtrim(delimiter, "\"");
		free(delimiter);
	}
	if (delimiter[0] == '\'' && delimiter[ft_strlen(delimiter) - 1] == '\'')
	{
		*quotes = 1;
		new = ft_strtrim(delimiter, "\'");
		free(delimiter);
	}
	return (new);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("/tmp/.file_heredoc_", num);
	free(num);
	return (file_name);
}
