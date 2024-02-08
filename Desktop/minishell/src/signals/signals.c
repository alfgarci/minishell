/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfgarci <alfgarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:55:18 by alfgarci          #+#    #+#             */
/*   Updated: 2024/02/07 00:05:09 by alfgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop(void)
{
	return (1);
}

void	sig_ctrl4(int sig)
{
	if (g_signal == IN_CMD)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	sig_ctrlc(int sig)
{
	(void) sig;
	if (g_signal == IN_CMD)
	{
		g_signal = STOP_HD;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
	}
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	rl_event_hook = loop;
	signal(SIGINT, sig_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}
