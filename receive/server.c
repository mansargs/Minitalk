/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:27:35 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/15 17:12:29 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static char	symbol = 0;
	static char	bit_count = 0;

	(void) context;
	if (signum == SIGUSR1)
		symbol |= (1 << (7 - bit_count));
	++bit_count;
	if (bit_count == 8)
	{
		if (symbol == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(symbol, 1);
		bit_count = 0;
		symbol = 0;
	}
	kill(info->si_pid, SIGUSR1);
	usleep(100);
}

int	main ()
{
	pid_t server;
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	server = getpid();
	ft_putstr_fd("Server PID ", 1);
	ft_putnbr_fd(server, 1);
	ft_putchar_fd('\n', 1);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
