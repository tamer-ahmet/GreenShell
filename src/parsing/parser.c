/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:18:46 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/04 20:57:00 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_parsing_errors(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if ((tmp->type == PIPE)
		|| (tmp->type == INRED && !tmp->next)
		|| (tmp->type == HEREDOC && !tmp->next)
		|| (tmp->type == OUTRED && !tmp->next)
		|| (tmp->type == APPEND && !tmp->next))
		return (syntax_error());
	while (tmp)
	{
		if (tmp->next)
		{
			if ((tmp->type == INRED && tmp->next->type != WORD)
				|| (tmp -> type == HEREDOC && tmp->next->type != WORD))
				return (syntax_error());
			else if (!tmp->next && tmp->type > 1)
				return (syntax_error());
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	data_prepare_loop(t_data *data, t_token *tokens)
{
	t_token		*current;
	t_command	*new_cmd;

	current = tokens;
	data -> commands_list = NULL;
	while (current)
	{
		new_cmd = create_command(current);
		if (!new_cmd)
			return ;
		if (data->commands_list == NULL)
			data->commands_list = new_cmd;
		else
			append_command(&data->commands_list, new_cmd);
		while (current && current->type != PIPE)
			current = current->next;
		if (current && current->type == PIPE)
			current = current->next;
	}
	return ;
}

int	parser(t_data *data)
{
	t_lexer		*lexer;
	t_token		*tokens;
	int			result;
	char		*str;

	result = 1;
	if (!data->line || ft_strlen(data->line) == 0)
		return (result);
	str = ft_strtrim(data->line, " ");
	lexer = init_lexer(str);
	tokens = lexer_tokenize(lexer);
	if (tokens)
		result = check_parsing_errors(tokens);
	if (!result)
		data_prepare_loop(data, tokens);
	free_parsing(lexer, tokens, str);
	return (result);
}
