/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:21:03 by atamer            #+#    #+#             */
/*   Updated: 2025/03/26 17:31:58 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	sep_count(char const *s, char c)
{
	int	i;
	int	sep;

	sep = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			sep++;
		while (s[i] && !(s[i] == c))
			i++;
	}
	return (sep);
}

static int	next_sep(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == c))
		i++;
	return (i);
}

static char	*ft_dup(char const *s, char c)
{
	int		len;
	int		i;
	char	*dup;

	i = 0;
	len = next_sep(s, c);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static void	*free_split(char **arr, int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		free (arr[k]);
		k++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	arr = malloc((sep_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s != '\0')
		{
			arr[i] = ft_dup(s, c);
			if (arr[i] == NULL)
				return (free_split(arr, i));
			i++;
		}
		while (*s && !(*s == c))
			s++;
	}
	arr[i] = 0;
	return (arr);
}
