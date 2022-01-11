/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:23:58 by njaros            #+#    #+#             */
/*   Updated: 2022/01/11 14:52:09 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(int err, char *to_free)
{
	if (err == 0)
	{
		ft_putendl_fd("bon déroulement du processus", 1);
		free(to_free);
		exit(EXIT_SUCCESS);
	}
	if (err == 1)
		ft_putendl_fd("je prends 2 arguments", 2);
	if (err == 3)
		ft_putendl_fd("erreur du processus kill", 2);
	if (err == 4)
		ft_putendl_fd("pas assez de memoire ou texte trop long", 2);
	if (err == 5)
		ft_putendl_fd("bug serveur", 2);
	free(to_free);
	exit(EXIT_FAILURE);
}

void	client_envoi_signal(int pid, int bug, char *str)
{
	if (bug == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			error(2, str);
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
			error(2, str);
	}
}
