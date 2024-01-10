/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:07:24 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/09 14:29:18 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int		c = 0;
	static int		i = 0;
	static pid_t	pid = 0;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid)
	{
		c = 0;
		i = 0;
		pid = 0;
		_print("\n");
	}
	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		c = (c << 1) + (signal == SIGUSR1);
		i++;
		if (i == 8)
		{
			write (1, &c, 1);
			i = 0;
			c = 0;
		}
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	siga;

	pid = getpid();
	siga.sa_sigaction = signal_handler;
	siga.sa_flags = SA_SIGINFO;
	siga.sa_mask = 0;
	sigaction(SIGUSR1, &siga, 0);
	sigaction(SIGUSR2, &siga, 0);
	_print("PID : [ ");
	print_number(pid);
	_print(" ]\n\n---------- MESSAGES ----------\n");
	while (1)
		pause();
	return (0);
}
