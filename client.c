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
	if (err == 2)
		ft_putendl_fd("le serveur a bugué", 2);
	if (err == 3)
		ft_putendl_fd("erreur du processus kill", 2);
	if (err == 4)
		ft_putendl_fd("pas assez de memoire ou texte trop long", 2);
	if (err == 5)
		ft_putendl_fd("bug serveur", 2);
	free(to_free);
	exit(EXIT_FAILURE);
}

int	envoi_bit_norminage(int pid, char c, int bit)
{
	if ((c & (0x80 >> bit)) == 0x80 >> bit)
	{
		if (kill(pid, SIGUSR2) == -1)
			return (0);
	}
	else if (kill(pid, SIGUSR1) == -1)
		return (0);
	return (1);
}

void	envoi_bit(int serv_pid, char *av2, int etat)
{
	static char	*cpy = 0;
	static int	bit = -1;
	static int	char_lu = 0;
	static int 	pid = 0;

	if (etat == 2)
		error(5, cpy);
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
	if (!envoi_bit_norminage(pid, cpy[char_lu], bit))
		error(3, cpy);
	if (!cpy[char_lu] && bit == 7)
		error(0, cpy);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		envoi_bit(0, NULL, 0);
	else
		envoi_bit(0, NULL, 2);
}

int	main(int ac, char **av)
{
	int					pid;

	if (ac != 3)
		(error(1, NULL));
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	envoi_bit(pid, av[2], 1);
	while (1)
		pause();
}