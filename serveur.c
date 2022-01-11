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

char	*ajout_char(char *str, char c, int reinit)
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
	if (sig == SIGUSR2)
		c = c | (0x80 >> bit_pos);
	bit_pos++;
	if (bit_pos >= 8)
	{
		if (c)
			str = ajout_char(str, c, 0);
		else
		{
			ft_putstr_fd(str, 1);
			str = ajout_char(str, c, 1);
		}
		bit_pos = 0;
		c = 0x00;
	}
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
		error(3, str);
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
