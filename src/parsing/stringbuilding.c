/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:59:24 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/04 21:28:42 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define INITIAL_CAPACITY 32

static void	sb_grow(t_stringbuilder *sb, size_t min_cap)
{
	size_t	new_cap;
	char	*new_str;

	new_cap = sb->cap * 2;
	if (new_cap < min_cap)
		new_cap = min_cap;
	new_str = malloc(new_cap);
	if (!new_str)
		return ;
	ft_memcpy(new_str, sb->str, sb->len);
	free(sb->str);
	sb->str = new_str;
	sb->cap = new_cap;
}

t_stringbuilder	*sb_new(void)
{
	t_stringbuilder	*sb;

	sb = malloc(sizeof(t_stringbuilder));
	if (!sb)
		return (NULL);
	sb->str = malloc(INITIAL_CAPACITY);
	if (!sb->str)
	{
		free(sb);
		return (NULL);
	}
	sb->len = 0;
	sb->cap = INITIAL_CAPACITY;
	return (sb);
}

void	sb_append(t_stringbuilder *sb, char *s)
{
	size_t	s_len;

	if (!sb || !s)
		return ;
	s_len = ft_strlen(s);
	if (sb->len + s_len + 1 > sb->cap)
		sb_grow(sb, sb->len + s_len + 1);
	ft_memcpy(sb->str + sb->len, s, s_len);
	sb->len += s_len;
	sb->str[sb->len] = '\0';
}

void	sb_append_char(t_stringbuilder *sb, char c)
{
	if (sb->len + 2 > sb->cap)
		sb_grow(sb, sb->len + 2);
	sb->str[sb->len++] = c;
	sb->str[sb->len] = '\0';
}

char	*sb_build(t_stringbuilder *sb)
{
	char	*final;

	if (!sb)
		return (NULL);
	final = malloc(sb->len + 1);
	if (!final)
		return (NULL);
	ft_memcpy(final, sb->str, sb->len);
	final[sb->len] = '\0';
	sb_free(sb);
	return (final);
}
