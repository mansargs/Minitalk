/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:15:06 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/21 22:15:07 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_list	*g_clients;

static void	restore_symbols(int signum, t_list *client, t_data **data)
{
	*data = (t_data *)((client)->content);
	(*data)->time = 0;
	if (signum == SIGUSR1)
		(*data)->symbol[0] |= (1 << (7 - (*data)->bit_count));
	(*data)->bit_count++;
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	t_list	*client;
	t_data	*data;

	(void)context;
	client = get_client(info->si_pid);
	if (!client)
		return ;
	restore_symbols(signum, client, &data);
	if (data->bit_count == 8)
	{
		if (!printing_behavior(&client))
			return ;
		if (!client || !client->content)
			return ;
		data = (t_data *)client->content;
		data->bit_count = 0;
		data->symbol[0] = 0;
	}
	if (client && client->content)
	{
		kill(info->si_pid, SIGUSR1);
		usleep(50);
	}
}

void	configure(struct sigaction *sa)
{
	pid_t	server;

	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = signal_handler;
	sigemptyset(&sa->sa_mask);
	server = getpid();
	ft_putstr_fd("Server PID ", 1);
	ft_putnbr_fd(server, 1);
	ft_putchar_fd('\n', 1);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	t_list				*cli;

	(void) argv;
	if (argc != 1)
	{
		ft_putstr_fd("Shouldn't take arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	configure(&sa);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		usleep(100000);
		cli = g_clients;
		while (cli)
		{
			((t_data *)(cli->content))->time++;
			cli = cli->next;
		}
		dead_inactive_clients();
		pause();
	}
	return (EXIT_SUCCESS);
}
