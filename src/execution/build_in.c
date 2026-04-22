/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:32:22 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:08:50 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(char *command)
{
	if (!command)
		return (-1);
	if (!ft_strcmp(command, "env"))
		return (ENV);
	else if (!ft_strcmp(command, "export"))
		return (EXPORT);
	else if (!ft_strcmp(command, "unset"))
		return (UNSET);
	else if ((str_contains(command, '=')) || (!ft_strcmp(command, "set")))
		return (ASSIGN);
	else if (!ft_strcmp(command, "minishell")
		|| !ft_strcmp(command, "./minishell"))
		return (SHELL);
	else if (!ft_strcmp(command, "exit"))
		return (EXIT);
	else if (!ft_strcmp(command, "cd"))
		return (CD);
	else if (!ft_strcmp(command, "pwd"))
		return (PWD);
	return (NO_BUILD_IN);
}

void	exec_pipe_build_in(t_data *data, int index, int command_id)
{
	if (command_id == ENV)
		print_env(data->envp);
	else if (command_id == EXPORT)
		execute_export(data, data->commands_array[index].command_strings);
	else if (command_id == UNSET)
		execute_unset(data, data->commands_array[index].command_strings);
	else if (command_id == ASSIGN)
		execute_assign(data, data->commands_array[index].command_strings);
	else if (command_id == SHELL)
		execute_shell(data);
	else if (command_id == EXIT)
		check_exit(data);
	else if (command_id == PWD)
		execute_pwd();
	free_arr(data->commands_array->command_strings);
	free(data->commands_array->tokens);
	free(data->commands_array);
	free_arr(data->envp);
	free_arr(data->set);
	exit(0);
}
