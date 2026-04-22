/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:23:42 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 13:06:39 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_shell_level(t_data *data)
{
	int		index;
	int		level;
	char	*sh;

	level = 0;
	index = -1;
	while (data->envp[++index])
	{
		if (ft_strncmp(data->envp[index], "SHLVL", 5) == 0)
			level = ft_atoi(ft_envstr(data->envp[index],
						"=", ft_strlen(data->envp[index])));
	}
	sh = ft_itoa(level + 1);
	assign_exported(data->envp, "SHLVL", sh);
	free(sh);
	assign_exported(data->envp, "SHELL", "greenshell");
	return (level);
}

int	check_exit_args(t_data *data, t_store *store)
{
	if (data->commands_list->command_strings[2])
	{
		write(2, "GreenShell: exit: too many arguments\n", 37);
		g_exit_status = 1;
		return (1);
	}
	if (ft_isalldigits(data->commands_list->command_strings[1]))
	{
		g_exit_status = 2;
		store->flag = 1;
		write(2, "GreenShell: exit: numeric argument required\n", 44);
	}
	store->count = ft_atoi(data->commands_list->command_strings[1]);
	return (0);
}

int	check_exit(t_data *data)
{
	t_store	store;

	store.index = -1;
	store.flag = 0;
	store.count = 0;
	if (data->commands_list->command_strings[1]
		&& check_exit_args(data, &store) == 1)
		return (1);
	while (data->envp[++store.index])
	{
		if (ft_strncmp(data->envp[store.index], "SHLVL", 5) == 0)
			store.path = ft_envstr(data->envp[store.index],
					"=", ft_strlen(data->envp[store.index]));
	}
	store.num = ft_atoi(store.path) - 1;
	store.path = ft_itoa(store.num);
	assign_exported(data->envp, "SHLVL", store.path);
	if (store.flag != 1)
		g_exit_status = (unsigned char)store.count;
	free(store.path);
	if (store.num == data->level)
		exit(g_exit_status);
	return (0);
}

void	execute_shell(t_data *data)
{
	t_store	store;

	store.index = -1;
	while (data->envp[++store.index])
	{
		if (ft_strncmp(data->envp[store.index], "SHLVL", 5) == 0)
			store.path = ft_envstr(data->envp[store.index], "=",
					ft_strlen(data->envp[store.index]));
	}
	store.num = ft_atoi(store.path);
	store.num++;
	store.path = ft_itoa(store.num);
	assign_exported(data->envp, "SHLVL", store.path);
	free(store.path);
}
