/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:56:12 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:43:52 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_temp(t_data *data)
{
	char	*index_str;
	char	*file_name;
	int		index;

	index = 0;
	while (++index <= data->heredoc_count)
	{
		index_str = ft_itoa(index);
		file_name = ft_strjoin(".temp_", index_str);
		unlink(file_name);
		free(index_str);
		free(file_name);
	}
}

void	clean_data(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->command_count)
	{
		free_arr(data->commands_array[index].command_strings);
		free(data->commands_array[index].tokens);
	}
	free(data->commands_array);
}

void	close_and_wait(t_data *data, int id)
{
	int	index;
	int	status;
	int	pid;

	index = -1;
	while (++index < data->command_count - 1)
	{
		close(data->commands_array[index].fd[0]);
		close(data->commands_array[index].fd[1]);
	}
	index = -1;
	while (++index < data->command_count)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid == id)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}
