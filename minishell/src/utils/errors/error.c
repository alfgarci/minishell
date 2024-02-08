/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:17:50 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_error(char *str, t_instance *ins)
{
	ft_putendl_fd(str, STDERR_FILENO);
	ins->err_num = 1;
	reset_minishell(ins);
}

void	ctrl_d(t_instance *ins)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(ins->err_num);
}

int	exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(EXIT_NUMARG_ERROR, STDERR_FILENO);
	return (255);
}
