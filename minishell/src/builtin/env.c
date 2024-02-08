/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:44 by alfgarci          #+#    #+#             */
/*   Updated: 2024/01/30 21:41:53 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_instance *ins, t_command *cmd)
{
	int	i;

	i = -1;
	if (cmd->args[1])
		minishell_error(ENV_ERROR, ins);
	while (ins->envp[++i])
		ft_putendl_fd(ins->envp[i], STDOUT_FILENO);
	return (0);
}
