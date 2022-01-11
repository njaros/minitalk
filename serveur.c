/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:26:42 by njaros            #+#    #+#             */
/*   Updated: 2022/01/10 16:26:42 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <sys/errno.h>

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static char	c = 0x00;
	static int	bit_pos = 0;

	(void) ucontext;
	if (sig == SIGUSR2)
		c = c | (0x80 >> bit_pos);
	bit_pos++;
	if (bit_pos >= 8)
	{
		ft_putchar_fd(c, 1);
		bit_pos = 0;
		c = 0x00;
	}
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
	{
		ft_putendl_fd("Fail du kill", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGKILL);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
}
