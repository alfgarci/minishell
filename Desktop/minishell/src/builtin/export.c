/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 04:09:30 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/04 14:28:24 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_export(char *str)
{
	char	**aux_split;
	int		is_valid;

	is_valid = 1;
	aux_split = ft_split(str, '=');
	if (len_arr(aux_split) != 2)
		is_valid = 0;
	if (len_arr(aux_split) == 1 && str[ft_strlen(str) - 1] == '=')
		is_valid = 1;
	free_split(aux_split);
	return (is_valid);
}

static void	add_or_mod_envp(t_instance *ins, char *arg)
{
	char	**tmp_split;
	int		i;
	int		is_found;
	char	*arg_save;

	tmp_split = ft_split(arg, '=');
	i = -1;
	is_found = 0;
	while (ins->envp[++i] && !is_found)
	{
		if (!ft_strncmp(ins->envp[i], tmp_split[0], ft_strlen(tmp_split[0])))
		{
			free(ins->envp[i]);
			arg_save = ft_strdup(arg);
			ins->envp[i] = expander_heredoc(ins, arg_save);
			is_found = 1;
		}
	}
	if (!is_found)
	{
		arg_save = ft_strdup(arg);
		ins->envp = append_to_array(ins->envp, expander_heredoc(ins, arg_save));
	}
	free_split(tmp_split);
}

int	export(t_instance *ins, t_command *cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!cmd->args[1])
		return (env(ins, cmd));
	while (cmd->args[++i])
	{
		if (is_valid_export(cmd->args[i]))
			add_or_mod_envp(ins, cmd->args[i]);
		else
		{
			ft_putstr_fd(EXPORT_ERROR, STDERR_FILENO);
			ft_putendl_fd(cmd->args[i], STDERR_FILENO);
			ret = 1;
		}
	}
	return (ret);
}
