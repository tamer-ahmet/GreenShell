/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:15:42 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/06 13:39:57 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	append_and_free(t_stringbuilder *sb, char *tmp)
{
	sb_append (sb, tmp);
	free (tmp);
}

static char	*expand_exit_status(int exit_status)
{
	char	*str;

	str = ft_itoa(exit_status);
	if (!str)
		return (NULL);
	return (str);
}

static int	make_env_var_assest(t_lexer	*lexer)
{
	if (ft_isalpha(lexer -> current_char) || lexer -> current_char == '_')
	{
		while (ft_isalnum(lexer->current_char) || lexer->current_char == '_')
			lexer_advance(lexer);
		return (0);
	}
	else
		return (1);
}

static char	*make_env_var(t_lexer *lexer)
{
	int		start;
	char	*var;
	char	*env;

	start = lexer -> pos;
	lexer_advance(lexer);
	if (lexer -> current_char == '?')
	{
		lexer_advance(lexer);
		return (expand_exit_status(g_exit_status));
	}
	if (make_env_var_assest(lexer))
		return (ft_strdup("$"));
	var = ft_strndup(lexer -> input + start + 1, lexer -> pos - start - 1);
	if (!var)
		return (NULL);
	env = getenv(var);
	free (var);
	if (!env)
		return (ft_strdup(""));
	return (ft_strdup(env));
}

char	*lexer_collect_word(t_lexer *lexer)
{
	t_stringbuilder	*sb;
	char			*tmp;

	sb = sb_new();
	while (lexer->current_char && !ft_strchr("><| ", lexer->current_char))
	{
		if (lexer->current_char == '"' || lexer->current_char == 39)
		{
			tmp = make_string(lexer);
			if (tmp)
				append_and_free(sb, tmp);
		}
		else if (lexer->current_char == '$')
		{
			tmp = make_env_var(lexer);
			if (tmp)
				append_and_free(sb, tmp);
		}
		else
		{
			sb_append_char(sb, lexer->current_char);
			lexer_advance(lexer);
		}
	}
	return (sb_build(sb));
}
