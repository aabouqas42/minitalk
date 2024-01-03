/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:07:24 by aabouqas          #+#    #+#             */
/*   Updated: 2024/01/03 14:11:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	_pn(int	n)
{
	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		char	c;
		c = n + 48;
		write (1, &c, 1);
	} else {
		_pn (n / 10);
		_pn (n % 10);
	}
}

void	_sig(int signal)
{
	static int c = 0;
	static int i = 0;

	if (signal == SIGUSR1)
		c = (c << 1) + 1;
	if (signal == SIGUSR2)
		c = (c << 1);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			write (1, "\n", 1);
		else
			write (1, &c, 1);
		c = 0;
		i = 0;
	}
}

int main()
{
	pid_t	pid;

	pid = getpid();
	write (1, "PID : ", 6);
	_pn(pid);
	write(1, "\n", 1);
	while (1)
	{
		signal(30, _sig);
		signal(31, _sig);
		pause();
	}
}