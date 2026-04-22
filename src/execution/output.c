/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:53:30 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:29:45 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	is_directory(char *cmd)
{
	write(2, "GreenShell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
	exit(126);
}

void	command_not_found(t_store *store)
{
	write(2, store->exec_arr[0], ft_strlen(store->exec_arr[0]));
	write(2, ": command not found\n", 20);
	if (store->exec_arr)
		free_arr(store->exec_arr);
	if (store->path_arr)
		free_arr(store->path_arr);
	exit(127);
}

void	*invalid_export(char **var_arr)
{
	write(2, "GreenShell: ", 12);
	write(2, "export: ", 8);
	write(2, "not a valid identifier\n", 23);
	g_exit_status = 1;
	free_arr(var_arr);
	return (NULL);
}

int	check_directory(char *path)
{
	struct stat	sb;

	if (!str_contains(path, '/'))
		return (0);
	if (stat(path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			return (1);
		else if (S_ISREG(sb.st_mode))
			return (0);
	}
	return (0);
}

void	check_echo(t_store *store)
{
	if (!store->exec_arr[1])
	{
		printf("\n");
		exit(0);
	}
	execute_echo(store->exec_arr);
	free_arr(store->exec_arr);
	exit(0);
}
