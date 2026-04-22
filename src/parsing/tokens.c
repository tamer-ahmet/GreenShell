/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:59 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/04 17:44:13 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token -> type = type;
	token -> value = ft_strdup(value);
	token -> prev = NULL;
	token -> next = NULL;
	return (token);
}

void	append_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !new)
		return ;
	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = new;
	new -> prev = tmp;
	return ;
}

static t_token	*token_collect_operator(t_lexer *lexer)
{
	if (lexer -> current_char == '>')
	{
		lexer_advance(lexer);
		if (lexer -> current_char == '>')
		{
			lexer_advance(lexer);
			return (new_token(APPEND, ">>"));
		}
		return (new_token(OUTRED, ">"));
	}
	else if (lexer -> current_char == '<')
	{
		lexer_advance(lexer);
		if (lexer -> current_char == '<')
		{
			lexer_advance(lexer);
			return (new_token(HEREDOC, "<<"));
		}
		return (new_token(INRED, "<"));
	}
	lexer_advance(lexer);
	return (new_token(PIPE, "|"));
}

t_token	*token_collect(t_lexer *lexer)
{
	char	*word;
	t_token	*token;

	while (lexer -> current_char)
	{
		lexer_skip_whitespace(lexer);
		if (!lexer->current_char)
			return (NULL);
		if (ft_strchr("><|", lexer -> current_char))
			return (token_collect_operator(lexer));
		else
		{
			word = lexer_collect_word(lexer);
			token = new_token(WORD, word);
			free (word);
			return (token);
		}
	}
	return (NULL);
}

t_token	*lexer_tokenize(t_lexer *lexer)
{
	t_token	*tokens;
	t_token	*new_token;

	tokens = NULL;
	while (lexer -> current_char)
	{
		lexer_skip_whitespace(lexer);
		new_token = token_collect(lexer);
		if (new_token && !ft_strlen(new_token->value))
		{
			free (new_token->value);
			free (new_token);
			lexer_advance(lexer);
		}
		else if (new_token)
			append_token(&tokens, new_token);
		else
			return (NULL);
	}
	return (tokens);
}
