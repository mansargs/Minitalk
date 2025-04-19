/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signal_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:11:02 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/19 16:15:34 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	reply_from_server(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGUSR1)
		g_stop = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd ("\nThe text has been successfully delivered.\n", \
					STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

void	setup_handler(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = reply_from_server;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
