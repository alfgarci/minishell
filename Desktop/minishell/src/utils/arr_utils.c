/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:56:47 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/04 14:22:16 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arrdup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	new = malloc((i + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (arr[++i] != NULL)
	{
		new[i] = ft_strdup(arr[i]);
		if (new[i] == NULL)
		{
			free_split(new);
			return (new);
		}
	}
	return (new);
}

char	*array_to_line(char **array)
{
	char	*resultado;
	int		total_len;
	int		i;

	total_len = 0;
	i = -1;
	while (array[++i] != NULL)
		total_len += ft_strlen(array[i]) + 1;
	resultado = (char *)malloc(total_len + 1);
	if (resultado == NULL)
		return (NULL);
	ft_strlcpy(resultado, array[0], total_len);
	i = 0;
	while (array[++i] != NULL)
	{
		ft_strlcat(resultado, " ", total_len + 1);
		ft_strlcat(resultado, array[i], total_len + 1);
	}
	return (resultado);
}

char	**append_to_array(char **arr, char *new)
{
	int		length;
	char	**new_arr;
	int		i;

	i = 0;
	length = len_arr(arr);
	new_arr = malloc((length + 2) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	while (i < length)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[length] = ft_strdup(new);
	new_arr[length + 1] = NULL;
	free(arr);
	free(new);
	return (new_arr);
}

int	len_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**delete_str_in_arr(char **arr, int num)
{
	char	**new_arr;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_arr = ft_calloc(len_arr(arr), sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (arr[++i])
		if (i != num)
			new_arr[++j] = ft_strdup(arr[i]);
	free_split(arr);
	return (new_arr);
}
