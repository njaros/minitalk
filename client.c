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

int	valeur_bit(char c, int bit)
{
	if ((c & (0x80 >> bit)) == 0x80 >> bit)
		return (1);
	else
		return (0);
}

void	envoi_bit(int serv_pid, char *av2, int etat)
{
	static char	*cpy = 0;
	static int	bit = -1;
	static int	char_lu = 0;
	static int	pid = 0;
	int			signal;

	if (etat == 1)
	{
		cpy = ft_strdup(av2);
		if (!cpy)
			error(4, NULL);
		pid = serv_pid;
	}
	if (++bit == 8)
	{
		bit = 0;
		char_lu++;
	}
	signal = valeur_bit(cpy[char_lu], bit);
	if (!cpy[char_lu] && bit == 7)
	{
		client_envoi_signal(pid, signal, cpy);
		error(0, cpy);
	}
	client_envoi_signal(pid, signal, cpy);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		envoi_bit(0, NULL, 0);
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
		(error(1, NULL));
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	envoi_bit(pid, av[2], 1);
	while (1)
		pause();
}
