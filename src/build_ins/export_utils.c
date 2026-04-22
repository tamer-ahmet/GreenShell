/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:45:10 by atamer            #+#    #+#             */
/*   Updated: 2025/05/05 11:45:46 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	contains_concat(char *str)
{
	int	index;
	int	len;

	index = 0;
	len = ft_strlen(str);
	while (index < len - 1)
	{
		if (str[index] == '+' && str[index + 1] == '=')
			return (1);
		index++;
	}
	return (0);
}

char	*cut_concat_name(char *str)
{
	char	*var_name;
	int		index;

	index = -1;
	var_name = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!var_name)
		return (NULL);
	while (str[++index])
	{
		if (str[index] == '+' && str[index + 1] == '=')
			break ;
		else
			var_name[index] = str[index];
	}
	var_name[index] = '\0';
	return (var_name);
}

char	*cut_concat_value(char *str)
{
	char	*value;
	int		index;
	int		j;

	index = 0;
	j = 0;
	value = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!value)
		return (NULL);
	while (str[index] != '=')
		index++;
	while (str[++index])
	{
		value[j] = str[index];
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	*concat_values(char **arr, char *name, char *value)
{
	char	*old_value;
	char	*new_value;
	int		index;
	int		len;

	index = -1;
	len = ft_strlen(name);
	while (arr[++index])
	{
		if (!ft_strncmp(arr[index], name, len) && arr[index][len] == '=')
		{
			old_value = cut_concat_value(arr[index]);
			new_value = ft_strjoin(old_value, value);
			assign_exported(arr, name, new_value);
			free(old_value);
			free(new_value);
		}
		else if (!ft_strcmp(arr[index], name))
		{
			assign_exported(arr, name, value);
		}
	}
	return (NULL);
}
