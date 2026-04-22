/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:18:00 by atamer            #+#    #+#             */
/*   Updated: 2025/03/26 16:18:43 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_lstsize(t_command *lst)
{
	int	length;

	length = 0;
	while (lst)
	{
		lst = lst -> next;
		length++;
	}
	return (length);
}
