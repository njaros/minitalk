#include "minitalk.h"

void	handler(int sig, siginfo_t *siginfo, void *ucontext)
{
	static unsigned char	c = 0x00;
	static int				bit_pos = 0;

	(void) ucontext;
	if (sig == SIGUSR2)
		c = c | (0x80 >> bit_pos);
	bit_pos++;
	if (bit_pos == 8)
	{
		if (c != 0)
			write(1, &c, 1);
		else
			write(1, "\n", 1);
		bit_pos = 0;
		c = 0x00;
	}
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
	{
		kill(siginfo->si_pid, SIGUSR2);
		ft_putendl_fd("serveur introuvable, fermeture processus", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	act;
	pid_t				pid;

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