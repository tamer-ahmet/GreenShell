/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:30:27 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 14:18:44 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*free_arr(char **arr)
{
	int	index;

	index = -1;
	if (arr)
	{
		while (arr[++index])
			free(arr[index]);
		free(arr);
		arr = NULL;
	}
	return (NULL);
}

void	sb_free(t_stringbuilder *sb)
{
	if (sb)
	{
		free(sb->str);
		free(sb);
	}
}

void	free_parsing(t_lexer *lexer, t_token *tokens, char *str)
{
	t_token	*tmp;

	if (!lexer && !tokens && !str)
		return ;
	if (lexer)
		free(lexer);
	if (str)
		free(str);
	if (tokens)
	{
		while (tokens)
		{
			tmp = tokens -> next;
			free (tokens -> value);
			free (tokens);
			tokens = tmp;
		}
	}
	return ;
}

void	free_commands_list(t_command *commands_list)
{
	t_command	*tmp;

	if (!commands_list)
		return ;
	while (commands_list -> prev != NULL)
		commands_list = commands_list -> prev;
	while (commands_list)
	{
		tmp = commands_list -> next;
		free_arr(commands_list->command_strings);
		free(commands_list->tokens);
		free(commands_list);
		commands_list = tmp;
	}
	return ;
}

void	ft_cleanup(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->commands_array)
		free(data->commands_array);
	if (data->commands_list)
		free_commands_list(data->commands_list);
}
