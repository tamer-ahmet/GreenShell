/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:36:11 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:47:40 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_export(char **envp, char *str)
{
	char	**new_env;
	int		len;
	int		index;

	index = -1;
	len = arr_len(envp);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (NULL);
	while (envp[++index])
		new_env[index] = ft_strdup(envp[index]);
	new_env[index] = ft_strdup(str);
	new_env[++index] = 0;
	free_arr(envp);
	return (new_env);
}

void	export_concat(t_data *data, char *str)
{
	char	*var_name;
	char	*value;

	var_name = cut_concat_name(str);
	value = cut_concat_value(str);
	if (check_env(data->envp, var_name) || check_export(data->envp, var_name))
	{
		concat_values(data->envp, var_name, value);
		concat_values(data->set, var_name, value);
	}
	else
	{
		data->envp = ft_export(data->envp, var_name);
		assign_exported(data->envp, var_name, value);
		data->set = ft_export(data->set, var_name);
		assign_exported(data->set, var_name, value);
	}
	free(var_name);
	free(value);
}

void	export_valid(t_data *data, char *str, char **var_arr)
{
	int		index;

	if (check_env(data->envp, var_arr[0]))
		return ;
	if (check_env(data->set, var_arr[0]))
	{
		index = -1;
		while (data->set[++index])
		{
			if (!ft_strncmp(data->set[index], var_arr[0],
					ft_varlen(data->set[index])))
				data->envp = ft_export(data->envp, data->set[index]);
		}
	}
	else if (!check_env(data->set, var_arr[0]))
	{
		data->envp = ft_export(data->envp, str);
		data->set = ft_export(data->set, str);
	}
}

void	*index_export(t_data *data, char *str)
{
	char	**var_arr;

	var_arr = ft_split(str, '=');
	if (!arr_len(var_arr) || !ft_isalpha(var_arr[0][0])
		|| str_contains(var_arr[0], '-'))
		return (invalid_export(var_arr));
	if (contains_concat(str))
		export_concat(data, str);
	else if (str_contains(str, '='))
	{
		if (check_env(data->envp, var_arr[0])
			|| check_export(data->envp, var_arr[0]))
		{
			data->envp = ft_unset(data->envp, var_arr[0]);
			data->set = ft_unset(data->set, var_arr[0]);
		}
		data->envp = ft_export(data->envp, str);
		data->set = ft_export(data->set, str);
	}
	else if (!str_contains(str, '='))
		export_valid(data, str, var_arr);
	free_arr(var_arr);
	return (NULL);
}

void	execute_export(t_data *data, char **command_strings)
{
	int	index;

	index = 1;
	if (arr_len(command_strings) == 1)
		print_export(data->envp);
	else
	{
		while (command_strings[index])
		{
			index_export(data, command_strings[index]);
			index++;
		}
	}
}
