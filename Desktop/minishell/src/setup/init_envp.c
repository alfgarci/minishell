/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:55:04 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/06 22:57:35 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
	return (ft_strdup("\0"));
}

void	init_home(t_instance *ins)
{
	int	i;

	i = -1;
	while (ins->envp[++i])
	{
		if (!ft_strncmp(ins->envp[i], "HOME=", 5))
		{
			ins->home = ft_substr(ins->envp[i], 5, ft_strlen(ins->envp[i]) - 5);
		}
	}
}

void	init_pwd(t_instance *ins)
{
	int	i;
	int	is_oldpwd;
	int	index_oldpwd;

	i = -1;
	is_oldpwd = 0;
	index_oldpwd = 0;
	while (ins->envp[++i])
	{
		if (!ft_strncmp(ins->envp[i], "PWD=", 4))
			ins->pwd = ft_substr(ins->envp[i],
					4, ft_strlen(ins->envp[i]) - 4);
		if (!ft_strncmp(ins->envp[i], "OLDPWD=", 7))
		{
			is_oldpwd = 1;
			index_oldpwd = i;
		}
	}
	if (is_oldpwd)
		ins->envp = delete_str_in_arr(ins->envp, index_oldpwd);
}

char	**mini_envp(t_instance *ins)
{
	char	**envp;
	char	*pwd_tmp;

	envp = malloc(3 * sizeof(char *));
	if (!envp)
		minishell_error(MALLOC_ERROR, ins);
	pwd_tmp = getcwd(NULL, sizeof(NULL));
	envp[0] = ft_strjoin("PWD=", pwd_tmp);
	free(pwd_tmp);
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = NULL;
	return (envp);
}

void	init_envp(t_instance *ins)
{
	char	*paths_tmp;
	int		i;
	char	*tmp;

	paths_tmp = get_path(ins->envp);
	ins->paths = ft_split(paths_tmp, ':');
	free(paths_tmp);
	i = -1;
	while (ins->paths[++i])
	{
		if (ft_strncmp(&ins->paths[i][ft_strlen(ins->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(ins->paths[i], "/");
			free(ins->paths[i]);
			ins->paths[i] = tmp;
		}
	}
}
