/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhornero <mhornero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:43:59 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/08 19:18:23 by mhornero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_to_delete(t_instance *ins, char *key)
{
	int		i;
	char	**tmp_split;

	i = -1;
	while (ins->envp[++i])
	{
		tmp_split = ft_split(ins->envp[i], '=');
		if (!ft_strncmp(tmp_split[0], key, ft_strlen(tmp_split[0])))
		{
			ins->envp = delete_str_in_arr(ins->envp, i);
			if (!ins->envp)
				minishell_error(MALLOC_ERROR, ins);
			free_split(tmp_split);
			break ;
		}
		free_split(tmp_split);
	}
}

int	unset(t_instance *ins, t_command *cmd)
{
	int	i;

	i = -1;
	if (!cmd->args[1])
	{
		ft_putendl_fd(UNSET_ERROR, STDERR_FILENO);
		return (1);
	}
	while (cmd->args[++i])
		try_to_delete(ins, cmd->args[i]);
	return (0);
}
