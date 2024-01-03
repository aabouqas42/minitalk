/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:11:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/03 14:12:03 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
			break;
		str++;
	}
	return (res * sign);
}

void	send_byte(pid_t pid, int c)
{
	int	i = 0;
	while (i < 8)
	{
		if (c & 128)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		usleep(100);
		c = c << 1;
		i++;
	}
}

int main(int ac, char *av[])
{
	if (ac == 3)
	{
		pid_t	pid;
		int		i;
		char	*str;

		pid = _atoi(av[1]);
		if (pid <= 0)
		{
			write (1, "\033[1;31minvalid process id aka PID\n\033[0m\n", 34);
			return (-1);
		}
		str = av[2];
		i = 0;
		while (str[i])
		{
			send_byte(pid, str[i]);
			i++;
		}
		send_byte(pid, '\0');
	}
}