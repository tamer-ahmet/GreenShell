/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:21:39 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/01 14:22:44 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
		index++;
	return (index);
}

int	ft_varlen(char *line)
{
	int	index;

	index = 0;
	if (!line)
		return (0);
	while (line[index] && line[index] != '=')
		index++;
	return (index);
}

int	arr_len(char **arr)
{
	int	index;

	if (arr == NULL)
		return (0);
	index = 0;
	while (arr[index])
		index++;
	return (index);
}
