/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:54:53 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 13:55:30 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	update_pwd_vars(t_data *data, char *oldpwd)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("cd"), 1);
	if (oldpwd)
		update_env(data, "OLDPWD", oldpwd);
	update_env(data, "PWD", cwd);
	return (0);
}

char	*get_env_value(t_data *data, char *key)
{
	int		i;
	size_t	key_len;

	if (!data->envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, key_len) == 0
			&& data->envp[i][key_len] == '=')
			return (data->envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}
