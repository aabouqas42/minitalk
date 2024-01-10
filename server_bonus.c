/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:08:41 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/09 17:18:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	show_char(int *c, int *i, int pid)
{
	if (*c == '\0')
	{
		kill (pid, SIGUSR1);
		return ;
	}
	write (1, c, 1);
	*c = 0;
	*i = 0;
}

void	signal_hundler(int signal, siginfo_t *info, void *context)
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
		write (1, "\n", 1);
	}
	if (signal == SIGUSR1 || signal == SIGUSR2)
	{
		c = (c << 1) + (signal == SIGUSR1);
		i++;
		if (i == 8)
			show_char(&c, &i, pid);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	siga;

	pid = getpid();
	_print("PID : [ ");
	print_number(pid);
	siga.sa_sigaction = signal_hundler;
	siga.sa_flags = SA_SIGINFO;
	siga.sa_mask = 0;
	sigaction(SIGUSR1, &siga, 0);
	sigaction(SIGUSR2, &siga, 0);
	_print(" ]\n---------- MESSAGES ----------\n");
	while (1)
		pause();
	return (0);
}
