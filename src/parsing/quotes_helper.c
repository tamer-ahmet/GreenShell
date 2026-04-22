/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:17:37 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 13:06:17 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_makestring_vars(t_lexer *lxr, char *q_char, int *start)
{
	*q_char = lxr -> current_char;
	lexer_advance(lxr);
	*start = lxr -> pos;
	return ;
}

void	quotes_append_and_free(char **result, char *tmp)
{
	*result = append_str(*result, tmp);
	free(tmp);
	return ;
}
