/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:36 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/01 13:14:11 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer -> input = input;
	lexer -> pos = 0;
	lexer -> current_char = lexer -> input[0];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer -> current_char != '\0' && lexer -> pos < ft_strlen(lexer->input))
	{
		lexer -> pos++;
		lexer -> current_char = lexer -> input[lexer->pos];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer -> current_char == ' ')
		lexer_advance(lexer);
}
