/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:14:02 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/08 19:14:04 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write (1, str, i);
}

void	print_number(int n)
{
	char	c;

	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		c = n + 48;
		write (1, &c, 1);
	}
	else
	{
		print_number (n / 10);
		print_number (n % 10);
	}
}

int	_atoi(char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = res * 10 + *str - 48;
		else
			break ;
		str++;
	}
	return (res * sign);
}
