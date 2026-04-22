/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:25:01 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 13:57:54 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*make_env_entry(char *key, char *value)
{
	size_t	len;
	char	*entry;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	entry = malloc(len);
	if (!entry)
		return (NULL);
	ft_strcpy(entry, key);
	ft_strcat(entry, "=");
	ft_strcat(entry, value);
	return (entry);
}

static void	up_env_helper(t_data *data, int i, char *new_entry)
{
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	j = 0;
	while (j < i)
	{
		new_env[j] = data->envp[j];
		j ++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(data->envp);
	data->envp = new_env;
}

void	update_env(t_data *data, char *key, char *value)
{
	int		i;
	int		key_len;
	char	*new_entry;

	if (!key || !value)
		return ;
	key_len = ft_strlen(key);
	new_entry = make_env_entry(key, value);
	if (!new_entry)
		return ;
	i = 0;
	while (data->envp && data->envp[i])
	{
		if (ft_strncmp(data->envp[i], key, key_len) == 0
			&& data->envp[i][key_len] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = new_entry;
			return ;
		}
		i++;
	}
	up_env_helper(data, i, new_entry);
}

static char	*get_target_path(t_data *data, char **cmd)
{
	char	*oldpwd;

	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
		return (get_env_value(data, "HOME"));
	if (ft_strcmp(cmd[1], "-") == 0)
	{
		oldpwd = get_env_value(data, "OLDPWD");
		if (!oldpwd)
			write(2, "cd: OLDPWD not set\n", 20);
		else
		{
			write(1, oldpwd, ft_strlen(oldpwd));
			write(1, "\n", 1);
		}
		return (oldpwd);
	}
	return (cmd[1]);
}

int	execute_cd(t_data *data, char **command_strings)
{
	char	*target;
	char	*oldpwd;
	int		status;
	int		flag;

	flag = 0;
	if ((!command_strings[1] || ft_strcmp(command_strings[1], "~") == 0))
		flag = 1;
	if (cd_too_many_args(flag, command_strings))
		return (1);
	oldpwd = get_env_value(data, "PWD");
	if (flag == 1)
		target = get_env_value(data, "HOME");
	else
		target = get_target_path(data, command_strings);
	if (!target)
		return (1);
	if (chdir(target) != 0)
	{
		g_exit_status = 1;
		return (perror("cd"), 1);
	}
	status = update_pwd_vars(data, oldpwd);
	return (status);
}
