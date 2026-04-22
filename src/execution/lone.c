/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:48:28 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 15:16:01 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_lone_build_in(t_data *data, int func)
{
	if (func == ENV)
		print_env(data->envp);
	else if (func == EXPORT)
		execute_export(data, data->commands_array->command_strings);
	else if (func == UNSET)
		execute_unset(data, data->commands_array->command_strings);
	else if (func == ASSIGN)
		execute_assign(data, data->commands_array->command_strings);
	else if (func == SHELL)
		execute_shell(data);
	else if (func == EXIT)
		check_exit(data);
	else if (func == CD)
		execute_cd(data, data->commands_array->command_strings);
	else if (func == PWD)
		execute_pwd();
	else if (func == -1)
		return ;
}

void	wait_lone(int id)
{
	int	status;

	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
}

void	execute_child(t_data *data, t_store *store)
{
	signal(SIGQUIT, SIG_DFL);
	create_exec_array(store);
	if (store->exec_arr[0] && !ft_strcmp(store->exec_arr[0], "echo"))
		check_echo(store);
	if (store->exec_arr[0] && check_directory(store->exec_arr[0]))
		is_directory(store->exec_arr[0]);
	if (store->count == 0)
		exit(0);
	store->path_arr = create_path(data->envp);
	if (store->path_arr)
	{
		store->command = find_command(store->path_arr, store->exec_arr);
		if (store->command)
			execve(store->command, store->exec_arr, data->envp);
	}
	command_not_found(store);
}

void	*lone_fork(t_data *data)
{
	t_store	store;

	store.num = 0;
	store.count = 0;
	store.curr_cmd = data->commands_array[0];
	store.id = fork();
	if (store.id == -1)
		return (NULL);
	else if (store.id == 0)
		execute_child(data, &store);
	wait_lone(store.id);
	return (0);
}

void	lone_command(t_data *data)
{
	int	func;

	if (search_heredoc(data))
		return ;
	func = is_built_in(data->commands_array->command_strings[0]);
	if (func)
		execute_lone_build_in(data, func);
	else
		lone_fork(data);
	clean_temp(data);
}
