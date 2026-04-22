/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerri- <mguerri-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:11:29 by mguerri-          #+#    #+#             */
/*   Updated: 2025/05/05 14:03:37 by mguerri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_error(void)
{
	printf("GreenShell: Syntax error\n");
	g_exit_status = 2;
	return (1);
}

int	cd_too_many_args(int flag, char **command_strings)
{
	if (flag == 0 && command_strings[2])
	{
		g_exit_status = 1;
		write(2, "GreenShell: cd: too many arguments\n", 36);
		return (1);
	}
	else
		return (0);
}
