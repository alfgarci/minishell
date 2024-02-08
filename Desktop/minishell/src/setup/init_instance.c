/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_instance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:55:08 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/06 22:55:42 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shlvl(t_instance *ins)
{
	int		i;
	char	**tmp_split;
	char	*str_lvl;
	int		old_lvl;

	i = -1;
	while (ins->envp[++i])
	{
		if (!ft_strncmp(ins->envp[i], "SHLVL=", 6))
		{
			tmp_split = ft_split(ins->envp[i], '=');
			old_lvl = ft_atoi(tmp_split[1]);
			free_split(tmp_split);
			str_lvl = ft_itoa(old_lvl + 1);
			free(ins->envp[i]);
			ins->envp[i] = ft_strjoin("SHLVL=", str_lvl);
			free(str_lvl);
		}
	}
}

void	init_rest_instance(t_instance *ins)
{
	ins->cmd_list = NULL;
	ins->token_list = NULL;
	if (ins->home)
	{
		free(ins->home);
		ins->home = NULL;
	}
	ins->num_pipes = 0;
	ins->reset = 0;
	ins->pid = NULL;
	ins->is_here = 0;
	ins->list_parser = NULL;
	ins->list_red_parser = NULL;
	g_signal = 0;
	init_envp(ins);
	init_home(ins);
}

void	init_instance(t_instance *ins, char **env)
{
	ins->err_num = 0;
	ins->pwd = NULL;
	ins->old_pwd = NULL;
	ins->home = NULL;
	if (env[0] == NULL)
		ins->envp = mini_envp(ins);
	else
	{
		ins->envp = arrdup(env);
		add_shlvl(ins);
	}
	init_pwd(ins);
	init_rest_instance(ins);
}
