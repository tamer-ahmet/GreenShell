/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:20:59 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:29:20 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	no_permission(char *command)
{
	write(2, "GreenShell: ", 12);
	write(2, command, ft_strlen(command));
	write(2, " : Permission denied\n", 21);
	exit(126);
}

char	*check_executable(char *command)
{
	if (str_contains(command, '/') && access(command, F_OK) != 0)
	{
		if (errno == ENOENT)
		{
			write(2, "GreenShell: ", 12);
			write(2, command, ft_strlen(command));
			write(2, ": No such file or directory\n", 28);
			exit(127);
		}
	}
	if (str_contains(command, '/') && access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (command);
		else
			no_permission(command);
	}
	return (NULL);
}

char	*find_command(char **path_arr, char **command_arr)
{
	int		i;
	char	*path;
	char	*command;
	char	*executable;

	i = 0;
	executable = check_executable(command_arr[0]);
	if (executable)
		return (executable);
	while (path_arr[i])
	{
		path = ft_strjoin(path_arr[i], "/");
		command = ft_strjoin(path, command_arr[0]);
		free(path);
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (command);
			else
				no_permission(command);
		}
		free(command);
		i++;
	}
	return (NULL);
}
