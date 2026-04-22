/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:27:30 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:29:03 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*assign_exported(char **envp, char *var, char *value)
{
	t_store	store;

	store.index = -1;
	store.num = -1;
	store.count = -1;
	while (envp[++store.index])
	{
		if (ft_strncmp(envp[store.index], var,
				ft_varlen(envp[store.index])) == 0)
		{
			store.temp = malloc(sizeof(char)
					* (ft_strlen(var) + ft_strlen(value) + 2));
			if (!store.temp)
				return (NULL);
			while (var[++store.num])
				store.temp[store.num] = var[store.num];
			store.temp[store.num] = '=';
			while (value[++store.count])
				store.temp[++store.num] = value[store.count];
			store.temp[++store.num] = '\0';
			free(envp[store.index]);
			envp[store.index] = store.temp;
		}
	}
	return (NULL);
}

int	check_assign(t_store	*store, char *command)
{
	if (!str_contains(command, '='))
	{
		write(2, "GreenShell: not a valid identifier\n", 35);
		g_exit_status = 1;
		return (1);
	}
	store->command_arr = ft_split(command, '=');
	if (!arr_len(store->command_arr))
	{
		write(2, command, ft_strlen(command));
		write(2, ": command not found\n", 20);
		g_exit_status = 127;
		free_arr(store->command_arr);
		return (1);
	}
	else if (!ft_isalpha(store->command_arr[0][0])
		|| str_contains(store->command_arr[0], '-'))
	{
		write(2, "GreenShell: not a valid identifier\n", 35);
		free_arr(store->command_arr);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	*assign_concat(t_data *data, char *command)
{
	char	*var_name;
	char	*value;

	var_name = cut_concat_name(command);
	value = cut_concat_value(command);
	if (check_env(data->envp, var_name) || check_export(data->envp, var_name))
		concat_values(data->envp, var_name, value);
	else if (check_env(data->set, var_name)
		|| check_export(data->set, var_name))
		concat_values(data->set, var_name, value);
	else
	{
		data->set = ft_export(data->set, var_name);
		assign_exported(data->set, var_name, value);
	}
	free(var_name);
	free(value);
	return (NULL);
}

void	*index_assign(t_data *data, char *command)
{
	t_store	store;

	if (check_assign(&store, command))
		return (NULL);
	else if (contains_concat(command))
		assign_concat(data, command);
	else if (check_env(data->envp, store.command_arr[0])
		|| check_export(data->envp, store.command_arr[0]))
	{
		data->envp = ft_unset(data->envp, store.command_arr[0]);
		data->set = ft_unset(data->set, store.command_arr[0]);
		data->envp = ft_export(data->envp, command);
		data->set = ft_export(data->set, command);
	}
	else if (check_env(data->set, store.command_arr[0])
		|| check_export(data->set, store.command_arr[0]))
	{
		data->set = ft_unset(data->set, store.command_arr[0]);
		data->set = ft_export(data->set, command);
	}
	else
		data->set = ft_export(data->set, command);
	free_arr(store.command_arr);
	return (NULL);
}

void	*execute_assign(t_data *data, char **command_strings)
{
	int	index;

	if (arr_len(command_strings) == 1 && !ft_strncmp(command_strings[0],
			"set", ft_strlen(command_strings[0])))
		print_env(data->set);
	else
	{
		index = 0;
		while (command_strings[index])
		{
			index_assign(data, command_strings[index]);
			index++;
		}
	}
	return (NULL);
}
