/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:20:08 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 14:09:30 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exclude_newline(char **command_strings)
{
	int	j;

	j = 0;
	if (command_strings[1][j] == '-' && command_strings[1][j + 1] == 'n')
	{
		j++;
		if (command_strings[1][j + 1] == '\0')
			return (0);
		while (command_strings[1][j] == 'n')
		{
			j++;
			if (command_strings[1][j + 1] == '\0')
				return (0);
		}
	}
	return (1);
}

void	execute_echo(char **command_strings)
{
	int	newline;
	int	word_count;
	int	i;

	newline = exclude_newline(command_strings);
	if (!newline)
		i = 2;
	else
		i = 1;
	word_count = arr_len(command_strings);
	while (i < word_count)
	{
		printf("%s", command_strings[i]);
		if (i != word_count - 1)
			printf(" ");
		i ++;
	}
	if (newline)
		printf("\n");
}
