/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:12:12 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 13:05:46 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = 0;
	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	if (str)
		free(str);
	return (new_str);
}

char	*append_str(char *str, char *suffix)
{
	int		len1;
	int		len2;
	char	*new_str;

	len1 = 0;
	len2 = 0;
	if (str)
		len1 = ft_strlen(str);
	else
		len1 = 0;
	if (suffix)
		len2 = ft_strlen(suffix);
	else
		len2 = 0;
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	if (suffix)
		ft_strcpy(new_str + len1, suffix);
	new_str[len1 + len2] = '\0';
	if (str)
		free(str);
	return (new_str);
}

static char	*get_var_value(char *str, int *i)
{
	int		var_start;
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*expanded;

	var_start = *i + 1;
	var_len = 0;
	while (ft_isvarchar(str[var_start + var_len]))
		var_len++;
	var_name = ft_strndup(str + var_start, var_len);
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);
	free(var_name);
	*i = var_start + var_len;
	if (var_value)
		expanded = append_str(NULL, var_value);
	else
		expanded = NULL;
	return (expanded);
}

static char	*expand_variables(char *str)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_itoa(g_exit_status);
			if (tmp)
				quotes_append_and_free(&result, tmp);
			i += 2;
		}
		else if (str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			tmp = get_var_value(str, &i);
			if (tmp)
				quotes_append_and_free(&result, tmp);
		}
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}

char	*make_string(t_lexer *lexer)
{
	char	quote_char;
	int		start_pos;
	int		length;
	char	*expanded;
	char	*raw_str;

	init_makestring_vars(lexer, &quote_char, &start_pos);
	while (lexer -> current_char && lexer -> current_char != quote_char)
		lexer_advance(lexer);
	if (lexer -> current_char != quote_char)
		return (NULL);
	length = lexer -> pos - start_pos;
	lexer_advance(lexer);
	if (length == 0)
		return (ft_strdup(""));
	raw_str = ft_strndup(lexer -> input + start_pos, length);
	if (!raw_str)
		return (NULL);
	if (quote_char == '"')
	{
		expanded = expand_variables(raw_str);
		free(raw_str);
		return (expanded);
	}
	return (raw_str);
}
