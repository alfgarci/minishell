/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:07:34 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/07 01:21:10 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define MALLOC_ERROR "Malloc error"
# define PIPE_ERROR "Pipe error"
# define FORK_ERROR "Fork error"
# define HERE_ERROR "Heredoc error"
# define RD_ERROR "Readline error"
# define PARSE_ERROR "minishell: parse error near "
# define PROMPT_MSG "\033[0;96mminishell> \033[0m"
# define RED_ARROW "\033[0;31m-> \033[0m"
# define GREEN_ARROW "\033[0;34m-> \033[0m"
# define QUOTE_MSG "dequote> "
# define HERE_MSG "heredoc> "
# define ARGS_ERROR "minishell dont acept arguments"
# define CD_HOME_ERROR "cd: HOME not set"
# define CD_OLDPWD_ERROR "cd: OLDPWD not set"
# define EXIT_ERROR "minishell: exit: too many arguments"
# define EXIT_NUMARG_ERROR " numeric argument required"
# define EXPORT_ERROR "export: not valid in this context: "
# define UNSET_ERROR "unset: not enough arguments"
# define ENV_ERROR "env: dont acept arguments"
# define CMD_NOT_FOUNF ": command not found"

#endif
