/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:42:38 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/04 21:27:45 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_trim(char i, char *set)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == i)
			return (1);
		j++;
	}
	return (0);
}

static char	*create_str(char *s1, int i, int len)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc((len - i + 1) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s1[i] && i <= len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	i;
	int	len;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (!(ft_strlen(set) > 0))
		return (ft_strdup(s1));
	len = ft_strlen(s1) - 1;
	while (check_trim(s1[i], set) == 1)
		i++;
	while (check_trim(s1[len], set) == 1 && len > 0)
		len--;
	if (len - i < 0)
		return (ft_strdup(""));
	return (create_str(s1, i, len));
}
