/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:17:41 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_indetical(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}

char	*strjoin_3(char	*s1, char *s2, char *s3)
{
	char	*str_tmp;
	char	*new;

	str_tmp = ft_strjoin(s1, s2);
	new = ft_strjoin(str_tmp, s3);
	free(str_tmp);
	return (new);
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	len;
	char	*dest;

	len = 0;
	while (len < n && src[len] != '\0')
		len++;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}
