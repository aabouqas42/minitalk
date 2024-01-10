/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:07:04 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/09 14:36:07 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_byte(pid_t pid, int c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 128)
		{
			if (kill (pid, SIGUSR1) == -1)
				return (-1);
		}
		else
		{
			if (kill (pid, SIGUSR2) == -1)
				return (-1);
		}
		usleep(85);
		c = c << 1;
		i++;
	}
	return (0);
}

int	send_message(pid_t pid, char *message)
{
	if (*message == 0)
	{
		_print("\nError : you can't send an empty message\n\n");
		exit(-1);
	}
	while (*message)
	{
		if (send_byte(pid, *message) == -1)
		{
			_print("Error !\n");
			exit(-1);
		}
		message++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	pid_t	pid;

	if (ac == 3)
	{
		pid = _atoi(av[1]);
		if (pid <= 0)
			return (_print("invalid process id aka PID\n"), -1);
		send_message(pid, av[2]);
	}
	else
	{
		_print("\nError !\n\nUSAGE : ");
		_print(av[0]);
		_print(" PID \"Hello 42\"\n");
		_print("\n[ Run the server program to get the PID ]\n\n");
		return (-1);
	}
	return (0);
}
