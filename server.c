/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:34:05 by njaros            #+#    #+#             */
/*   Updated: 2022/01/13 11:34:05 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	interrompt(char *to_free, int pid_to_int, int int_error)
{
	kill(pid_to_int, SIGUSR2);
	if (int_error == 1)
		error(4, to_free, 0);
	if (int_error == 2)
		error(3, to_free, 0);
}

char	*ajout_char(char *str, char c, int reinit, int pid)
{
	int			j;
	static int	i = 1;
	char		*charade;

	if (reinit == 1)
	{
		i = 1;
		free(str);
		return (NULL);
	}
	j = -1;
	charade = malloc(i + 1);
	if (!charade)
		interrompt(str, pid, 1);
	if (str)
	{
		while (str[++j])
			charade[j] = str[j];
	}
	charade[++i - 2] = c;
	charade[i - 1] = '\0';
	free(str);
	return (charade);
}

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static char	c = 0x00;
	static int	bit_pos = 0;
	static char	*str = NULL;

	(void) ucontext;
	if (siginfo->si_pid == 0)
		error(2, str, 0);
	if (sig == SIGUSR2)
		c = c | (0x80 >> bit_pos);
	bit_pos++;
	if (bit_pos >= 8)
	{
		if (c)
			str = ajout_char(str, c, 0, siginfo->si_pid);
		else
		{
			ft_putstr_fd(str, 1);
			str = ajout_char(str, c, 1, 0);
		}
		bit_pos = 0;
		c = 0x00;
	}
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
		interrompt(str, siginfo->si_pid, 2);
}

int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	sigaddset(&act.sa_mask, SIGKILL);
	act.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
}
