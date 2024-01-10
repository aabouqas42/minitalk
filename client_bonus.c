/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:11:58 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/09 16:56:29 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		usleep(100);
		c = c << 1;
		i++;
	}
	return (0);
}

void	send_message(pid_t pid, char *message)
{
	if (*message == 0)
	{
		_print("\nError : an empty message can't be sent\n\n");
		exit(-1);
	}
	while (*message)
	{
		if (send_byte(pid, *message) == -1)
		{
			_print("\nMESSAGE FAILED\n\n");
			exit(-1);
		}
		message++;
	}
}

void	sig_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		_print("\nMESSAGE RECEVIED\n\n");
		exit(0);
	}
}

int	main(int ac, char *av[])
{
	pid_t	pid;

	signal(SIGUSR1, sig_handler);
	if (ac == 3)
	{
		pid = _atoi(av[1]);
		if (pid <= 0)
			return (_print("\ninvalid process id aka PID\n\n"), -1);
		send_message(pid, av[2]);
		send_byte(pid, '\0');
	}
	else
	{
		_print("\nMESSAGE FAILED\n\nUSAGE : ");
		_print(av[0]);
		_print(" PID \"Hello 42\"\n");
		_print("\n[ Run the server_bonus program to get the PID ]\n\n");
		return (-1);
	}
	return (0);
}
