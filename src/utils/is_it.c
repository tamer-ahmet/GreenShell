/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:27:08 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/04 18:31:06 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isvarchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_isalldigits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i ++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i ++;
	}
	return (0);
}
