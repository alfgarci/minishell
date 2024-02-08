/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:31 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/07 01:05:08 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag_n(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) >= 2)
	{
		if (str[0] != '-')
			return (0);
		while (str[++i])
			if (str[i] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

int	my_echo(t_command *cmd)
{
	int	is_n;
	int	i;

	is_n = 0;
	i = 0;
	if (!cmd->args[1])
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
	{
		is_n = check_flag_n(cmd->args[1]);
		if (is_n)
			i++;
		while (cmd->args[++i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		if (is_n == 0)
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}
