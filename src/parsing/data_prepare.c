/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:10:12 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/02 10:58:34 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	number_of_tokens_until_pipe(t_token *tokens)
{
	t_token	*tmp;
	int		count;

	tmp = tokens;
	count = 0;
	while (tmp && tmp -> type != PIPE)
	{
		count ++;
		tmp = tmp -> next;
	}
	return (count);
}

int	*int_array_maker(t_token *tokens)
{
	int			*arr;
	t_token		*tmp;
	int			count;
	int			i;

	tmp = tokens;
	count = number_of_tokens_until_pipe(tokens);
	arr = malloc(sizeof(int) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < count && tmp -> type != PIPE)
	{
		arr[i] = tmp->type;
		tmp = tmp->next;
		i ++;
	}
	return (arr);
}

char	**char_array_maker(t_token *tokens)
{
	char	**arr;
	t_token	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (number_of_tokens_until_pipe(tokens) + 1));
	if (!arr)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		arr[i] = ft_strdup(tmp->value);
		i ++;
		tmp = tmp -> next;
	}
	arr[i] = 0;
	return (arr);
}

t_command	*create_command(t_token *tokens)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new -> tokens = int_array_maker(tokens);
	if (!new->tokens)
		return (NULL);
	new -> tokens_size = number_of_tokens_until_pipe(tokens);
	new -> command_strings = char_array_maker(tokens);
	if (!new -> command_strings)
		return (NULL);
	new -> prev = NULL;
	new -> next = NULL;
	return (new);
}

void	append_command(t_command **commands_list, t_command *new)
{
	t_command	*tmp;

	if (!commands_list || !new)
		return ;
	tmp = *commands_list;
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = new;
	new -> prev = tmp;
	return ;
}
