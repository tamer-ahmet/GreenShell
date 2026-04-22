/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:28:19 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:44:51 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**create_env(char **envp)
{
	char	**new_env;
	int		len;
	int		index;

	index = -1;
	len = arr_len(envp);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	while (envp[++index])
		new_env[index] = ft_strdup(envp[index]);
	new_env[index] = 0;
	return (new_env);
}

int	check_env(char **envp, char *var)
{
	int	index;
	int	len;

	index = -1;
	len = ft_strlen(var);
	while (envp[++index])
	{
		if ((!ft_strncmp(envp[index], var, len)) && (envp[index][len] == '='))
			return (1);
	}
	return (0);
}

int	check_export(char **envp, char *var)
{
	int	index;
	int	len;

	index = -1;
	len = ft_strlen(var);
	while (envp[++index])
	{
		if ((!ft_strncmp(envp[index], var, len))
			&& (ft_strlen(envp[index]) == len))
			return (1);
	}
	return (0);
}

void	print_env(char **envp)
{
	int	index;

	index = -1;
	if (envp)
	{
		while (envp[++index])
		{
			if (str_contains(envp[index], '='))
				printf("%s\n", envp[index]);
		}
	}
}

void	print_export(char **envp)
{
	int	index;

	index = -1;
	while (envp[++index])
		printf("declare -x %s\n", envp[index]);
}
