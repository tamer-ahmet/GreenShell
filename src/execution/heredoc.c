/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:38:03 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:29:22 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	read_heredoc(t_command curr_cmd, int token_index, t_store *store)
{
	while (!store->flag && !g_exit_status)
	{
		store->temp = readline("> ");
		if (!store->temp)
		{
			g_exit_status = 0;
			change_tokens(curr_cmd, token_index, store->command, store->path);
			return (1);
		}
		if (ft_strncmp(store->temp, curr_cmd.command_strings[token_index + 1],
				ft_strlen(store->temp)))
		{
			write(store->id, store->temp, ft_strlen(store->temp));
			write(store->id, "\n", 1);
		}
		else
			store->flag = 1;
		free(store->temp);
	}
	close(store->id);
	return (0);
}

int	shift_heredoc(t_command curr_cmd, int token_index, int *heredoc_count)
{
	t_store	store;

	store.flag = 0;
	g_exit_status = 0;
	store.command = ft_itoa(++(*heredoc_count));
	store.path = ft_strjoin(".temp_", store.command);
	store.id = open(store.path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (store.id == -1)
		heredoc_exit();
	signal(SIGINT, handle_heredoc_signal);
	if (read_heredoc(curr_cmd, token_index, &store) == 1)
		return (1);
	change_tokens(curr_cmd, token_index, store.command, store.path);
	if (g_exit_status == 130)
		return (2);
	return (0);
}

int	check_heredoc(t_data *data, int count)
{
	int			command_index;
	int			token_index;
	int			result;
	t_command	curr_cmd;

	data->heredoc_count = 0;
	command_index = -1;
	while (++command_index < count)
	{
		curr_cmd = data->commands_array[command_index];
		token_index = -1;
		while (++token_index < curr_cmd.tokens_size)
		{
			if (curr_cmd.tokens[token_index] == HEREDOC)
			{
				result = shift_heredoc(curr_cmd, token_index,
						&data->heredoc_count);
				if (result == 1 || result == 2)
					return (result);
			}
		}
	}
	return (0);
}

int	search_heredoc(t_data *data)
{
	int	here_doc;

	here_doc = check_heredoc(data, data->command_count);
	if (here_doc == 1)
	{
		clean_temp(data);
		g_exit_status = 0;
		return (1);
	}
	else if (here_doc == 2)
	{
		clean_temp(data);
		g_exit_status = 130;
		return (1);
	}
	return (0);
}
