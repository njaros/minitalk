/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:23:58 by njaros            #+#    #+#             */
/*   Updated: 2022/01/13 16:13:46 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(int err, char *to_free, int serv_err)
{
	if (serv_err == 2)
		ft_putendl_fd("crah serveur", 2);
	if (err == 0 && serv_err != 2)
	{
		ft_putendl_fd("bon déroulement du processus", 1);
		free(to_free);
		exit(EXIT_SUCCESS);
	}
	if (err == 1)
		ft_putendl_fd("je prends 2 arguments", 2);
	if (err == 2)
		ft_putendl_fd("bug kernel ou mauvaise gestion signaux UNIX", 2);
	if (err == 3)
		ft_putendl_fd("erreur du processus kill", 2);
	if (err == 4)
		ft_putendl_fd("pas assez de memoire ou texte trop long", 2);
	free(to_free);
	exit(EXIT_FAILURE);
}
