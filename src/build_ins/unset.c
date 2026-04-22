/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:44:42 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:48:21 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_unset(t_data *data, char **command_strings)
{
	int	index;

	index = 1;
	while (command_strings[index])
	{
		data->envp = ft_unset(data->envp, command_strings[index]);
		data->set = ft_unset(data->set, command_strings[index]);
		index++;
	}
}

int	check_unset(char *var, char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(var, str, len) == 0 && var[len] == '=')
		return (1);
	if (ft_strncmp(var, str, len) == 0 && len == ft_strlen(var))
		return (1);
	return (0);
}

char	**ft_unset(char **envp, char *var)
{
	char	**new_env;
	int		index;
	int		j;

	index = -1;
	j = -1;
	new_env = malloc(sizeof(char *) * (arr_len(envp) + 1));
	if (!new_env)
		return (NULL);
	while (envp[++index])
	{
		if (check_unset(envp[index], var) == 0)
			new_env[++j] = ft_strdup(envp[index]);
	}
	new_env[++j] = 0;
	free_arr(envp);
	return (new_env);
}
