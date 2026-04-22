/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:56:02 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 14:30:06 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	file_permission(char *file_name)
{
	write(2, "GreenShell: ", 12);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": Permission denied\n", 21);
	exit(1);
}

void	*exec_inredirection(t_store *store)
{
	int		infile;
	char	*file_name;

	store->num++;
	file_name = store->command_arr[store->num];
	infile = open(file_name, O_RDONLY);
	if (infile == -1)
	{
		if (errno == ENOENT)
		{
			write(2, "GreenShell: ", 12);
			write(2, file_name, ft_strlen(file_name));
			write(2, ": No such file or directory\n", 28);
			exit(1);
		}
		else if (errno == EACCES)
			file_permission(file_name);
		return (0);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	store->num++;
	return (0);
}

void	*exec_outredirection(t_store *store)
{
	int		out_file;
	char	*file_name;

	store->num++;
	file_name = store->command_arr[store->num];
	out_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (out_file == -1)
	{
		if (errno == EACCES)
			file_permission(file_name);
		return (0);
	}
	dup2(out_file, STDOUT_FILENO);
	close(out_file);
	store->num++;
	return (0);
}

void	*exec_append(t_store *store)
{
	int		out_file;
	char	*file_name;

	store->num++;
	file_name = store->command_arr[store->num];
	out_file = open(store->command_arr[store->num], O_WRONLY | O_APPEND
			| O_CREAT, 0600);
	if (out_file == -1)
	{
		if (errno == EACCES)
			file_permission(file_name);
		return (0);
	}
	dup2(out_file, STDOUT_FILENO);
	close(out_file);
	store->num++;
	return (0);
}

void	*create_exec_array(t_store *store)
{
	store->command_arr = store->curr_cmd.command_strings;
	store->len = arr_len(store->command_arr);
	store->exec_arr = malloc(sizeof(char *) * (store->len + 1));
	if (!store->exec_arr)
		return (NULL);
	while (store->num < store->len)
	{
		if (store->curr_cmd.tokens[store->num] == WORD)
			store->exec_arr[store->count++] = ft_strdup
				(store->command_arr[store->num++]);
		else if (store->curr_cmd.tokens[store->num] == INRED)
			exec_inredirection(store);
		else if (store->curr_cmd.tokens[store->num] == OUTRED)
			exec_outredirection(store);
		else if (store->curr_cmd.tokens[store->num] == APPEND)
			exec_append(store);
	}
	store->exec_arr[store->count] = 0;
	free_arr(store->command_arr);
	return (0);
}
