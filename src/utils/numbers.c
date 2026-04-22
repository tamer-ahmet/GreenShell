/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamer <atamer@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:00 by mguerri-          #+#    #+#             */
/*   Updated: 2025/03/26 16:01:28 by atamer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_power(int j)
{
	int	result;

	result = 1;
	while (j > 0)
	{
		result *= 10;
		j--;
	}
	return (result);
}

static char	*create_str(long n, int len, int sign)
{
	char	*str;
	int		i;
	int		lt;

	i = 0;
	lt = len;
	if (sign == -1)
		lt++;
	str = malloc((lt + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (sign == -1)
	{
		str[i] = '-';
		i++;
	}
	while (len > 0)
	{
		str[i] = n / get_power(len - 1) + 48;
		n = n % get_power(len - 1);
		i++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	long	dc;
	long	num;

	num = n;
	sign = 1;
	len = 1;
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}
	dc = num;
	while (dc > 9)
	{
		dc /= 10;
		len++;
	}
	return (create_str(num, len, sign));
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	return (result * sign);
}
