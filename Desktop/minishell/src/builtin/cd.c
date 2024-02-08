/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:42:46 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/06 22:02:58 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_path(t_instance *ins)
{
	char	*tmp;

	tmp = ft_strdup(ins->pwd);
	if (ins->old_pwd)
		free(ins->old_pwd);
	ins->old_pwd = tmp;
	free(ins->pwd);
	ins->pwd = getcwd(NULL, sizeof(NULL));
}

static int	cd_home(t_instance *ins)
{
	int	ret;

	ret = chdir(ins->home);
	if (ret != 0)
		ft_putendl_fd(CD_HOME_ERROR, STDERR_FILENO);
	return (ret);
}

static int	cd_oldpwd(t_instance *ins)
{
	int	ret;

	ret = chdir(ins->old_pwd);
	if (ret != 0)
		ft_putendl_fd(CD_OLDPWD_ERROR, STDERR_FILENO);
	return (ret);
}

static void	update_env(t_instance *ins)
{
	int		i;
	char	*tmp;

	i = -1;
	while (ins->envp[++i])
	{
		if (!ft_strncmp(ins->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", ins->pwd);
			free(ins->envp[i]);
			ins->envp[i] = tmp;
		}
		else if (!ft_strncmp(ins->envp[i], "OLDPWD=", 7) && ins->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", ins->old_pwd);
			free(ins->envp[i]);
			ins->envp[i] = tmp;
		}
	}
}

int	cd(t_instance *ins, t_command *cmd)
{
	int	ret;

	if (!cmd->args[1])
		ret = cd_home(ins);
	else if (is_str_indetical(cmd->args[1], "-"))
		ret = cd_oldpwd(ins);
	else
	{
		ret = chdir(cmd->args[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			perror(" ");
			ret = 1;
		}
	}
	if (ret != 0)
		return (1);
	change_path(ins);
	update_env(ins);
	return (0);
}
