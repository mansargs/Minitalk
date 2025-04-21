/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signal_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:14:31 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/21 22:14:32 by mansargs         ###   ########.fr       */
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
		ft_putstr_fd ("\nThe text has been successfully delivered.\n",
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
