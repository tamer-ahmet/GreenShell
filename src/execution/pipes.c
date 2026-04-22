/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:56:49 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:12:55 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipe_redirect(t_data *data, int index, int len)
{
	int	num;

	if (index == 0)
		dup2(data->commands_array[0].fd[1], STDOUT_FILENO);
	else if (index == len)
		dup2(data->commands_array[len - 1].fd[0], STDIN_FILENO);
	else
	{
		dup2(data->commands_array[index - 1].fd[0], STDIN_FILENO);
		dup2(data->commands_array[index].fd[1], STDOUT_FILENO);
	}
	num = -1;
	while (++num < len)
	{
		close(data->commands_array[num].fd[0]);
		close(data->commands_array[num].fd[1]);
	}
}

void	*create_pipe_exec_array(t_store *store, t_data *data, int index)
{
	store->num = 0;
	store->count = 0;
	store->command_arr = data->commands_array[index].command_strings;
	store->exec_arr = malloc(sizeof(char *)
			* (data->commands_array[index].tokens_size + 1));
	if (!store->exec_arr)
		return (NULL);
	while (store->num < data->commands_array[index].tokens_size)
	{
		if (data->commands_array[index].tokens[store->num] == WORD)
			store->exec_arr[store->count++] = ft_strdup
				(store->command_arr[store->num++]);
		else if (data->commands_array[index].tokens[store->num] == INRED)
			exec_inredirection(store);
		else if (data->commands_array[index].tokens[store->num] == OUTRED)
			exec_outredirection(store);
		else if (data->commands_array[index].tokens[store->num] == APPEND)
			exec_append(store);
	}
	store->exec_arr[store->count] = 0;
	if (store->count == 0)
		exit(0);
	return (0);
}

void	*execute_order(t_data *data, int index, int len)
{
	t_store	store;

	pipe_redirect(data, index, len);
	store.id = is_built_in(data->commands_array[index].command_strings[0]);
	if (store.id)
		exec_pipe_build_in(data, index, store.id);
	else
	{
		create_pipe_exec_array(&store, data, index);
		if (store.exec_arr[0] && !ft_strcmp(store.exec_arr[0], "echo"))
			check_echo(&store);
		if (store.exec_arr[0] && check_directory(store.exec_arr[0]))
			is_directory(store.exec_arr[0]);
		store.path_arr = create_path(data->envp);
		if (store.path_arr)
		{
			store.command = find_command(store.path_arr, store.exec_arr);
			if (store.command)
				execve(store.command, store.exec_arr, data->envp);
		}
		command_not_found(&store);
	}
	return (0);
}

void	*execute_pipes(t_data *data)
{
	t_store	store;

	store.index = -1;
	if (search_heredoc(data))
		return (NULL);
	while (++store.index < data->command_count - 1)
	{
		if (pipe(data->commands_array[store.index].fd) == -1)
			return (NULL);
	}
	store.index = -1;
	while (++store.index < data->command_count)
	{
		store.id = fork();
		if (store.id == -1)
			return (NULL);
		if (store.id == 0)
			execute_order(data, store.index, data->command_count - 1);
	}
	close_and_wait(data, store.id);
	clean_temp(data);
	return (0);
}
