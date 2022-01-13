/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:25:25 by njaros            #+#    #+#             */
/*   Updated: 2022/01/10 16:25:25 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	client_envoi_signal(int pid, int signal, char *str)
{
	if (signal == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			error(3, str, 0);
	}
	else if (signal == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(3, str, 0);
	}
}

void	envoi_bit(int serv_pid, char *av2, int etat)
{
	static char	*cpy = 0;
	static int	bit = -1;
	static int	char_lu = 0;
	static int	pid = 0;
	int			signal;

	if (bit == 8 || etat == 2)
		error(0, cpy, etat);
	if (etat == 1)
	{
		cpy = ft_strdup(av2);
		if (!cpy)
			error(4, NULL, 0);
		pid = serv_pid;
	}
	if (++bit == 8)
	{
		bit = 0;
		char_lu++;
	}
	signal = ((cpy[char_lu] & (0x80 >> bit)) == 0x80 >> bit);
	if (!cpy[char_lu] && bit == 7)
		bit++;
	client_envoi_signal(pid, signal, cpy);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		envoi_bit(0, NULL, 0);
	if (sig == SIGUSR2)
		envoi_bit(0, NULL, 2);
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
		(error(1, NULL, 0));
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	envoi_bit(pid, av[2], 1);
	while (1)
		pause();
}
