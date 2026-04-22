/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:07:25 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 15:16:39 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	child_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_child(void)
{
	signal(SIGINT, child_sigint);
}
