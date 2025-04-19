/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:27:35 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/19 14:51:01 by lenovo           ###   ########.fr       */
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

static void	print_timeout_and_clear(t_list *cli)
{
	ft_putstr_fd("\nTimeout for PID ", 1);
	ft_putnbr_fd(((t_data *)cli->content)->cid, 1);
	write(1, "\n", 1);
	ft_lstdelone(cli, clear_content);
}

static void	dead_inactive_clients(void)
{
	t_list		*cli;
	t_list		*prev;

	cli = g_clients;
	prev = NULL;
	while (cli)
	{
		if (((t_data *)cli->content)->time > 150)
		{
			if (prev)
				prev->next = cli->next;
			else
				g_clients = cli->next;
			print_timeout_and_clear(cli);
			if (prev)
				cli = prev->next;
			else
				cli = g_clients;
			continue ;
		}
		prev = cli;
		cli = cli->next;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				server;
	t_list				*cli;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	server = getpid();
	ft_putstr_fd("Server PID ", 1);
	ft_putnbr_fd(server, 1);
	ft_putchar_fd('\n', 1);
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
}
