/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:39:01 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:29:29 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_heredoc_signal(int signum)
{
	if (signum == SIGINT)
		g_exit_status = 130;
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
}

void	change_tokens(t_command curr_cmd, int token_index,
			char *index_str, char *file_name)
{
	curr_cmd.tokens[token_index] = INRED;
	free(curr_cmd.command_strings[token_index]);
	free(curr_cmd.command_strings[token_index + 1]);
	curr_cmd.command_strings[token_index] = ft_strdup("<");
	curr_cmd.command_strings[token_index + 1] = ft_strdup(file_name);
	free(index_str);
	free(file_name);
}

void	heredoc_exit(void)
{
	write(2, "GreenShell: ", 12);
	write(2, ": heredoc file problem\n", 23);
	exit(1);
}
