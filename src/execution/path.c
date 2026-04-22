/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:22:54 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 12:01:58 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_envstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (little[i] == '\0')
		return (big);
	while (big[i])
	{
		while (big[i + n] == little[n] && big[i + n] != '\0' && (i + n) < len)
		{
			n++;
			if (little[n] == '\0')
				return (big + i + 1);
		}
		n = 0;
		i++;
	}
	return (0);
}

char	**create_path(char **envp)
{
	int		i;
	int		control;
	char	*path;
	char	**path_arr;

	i = 0;
	control = 0;
	path = NULL;
	while (envp[i] && control == 0)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = ft_envstr(envp[i], "=", ft_strlen(envp[i]));
			control = 1;
		}
		i++;
	}
	if (path)
	{
		path_arr = ft_split(path, ':');
		return (path_arr);
	}
	return (NULL);
}
