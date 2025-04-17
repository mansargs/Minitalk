/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:27:35 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/17 18:10:15 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_list	*clients = NULL;

void	clear_content(void *content)
{
	if (!content)
		return;
	free(((t_data *)content)->text);
	free(content);
}

void	find_and_delete_client(t_list **client_ptr)
{
	t_list	*pre;
	t_list	*client;

	client = *client_ptr;
	if (!client)
		return;
	if (client == clients)
		clients = clients->next;
	else
	{
		pre = clients;
		while (pre && pre->next != client)
			pre = pre->next;
		if (pre && pre->next == client)
			pre->next = client->next;
	}
	ft_lstdelone(client, clear_content);
	*client_ptr = NULL;
}

int	printing_behavior(t_list **client_ptr)
{
	char	*temp;
	t_data	*data;

	if (!client_ptr || !*client_ptr)
		return (0);

	data = (t_data *)((*client_ptr)->content);

	if (data->symbol[0] == '\0')
	{
		ft_putstr_fd(data->text, 1);
		ft_putchar_fd('\n', 1);
		kill(data->cid, SIGUSR2);
		find_and_delete_client(client_ptr);
		usleep(20);
	}
	else
	{
		temp = ft_strjoin(data->text, data->symbol);
		if (!temp)
			return (0);
		free(data->text);
		data->text = temp;
	}
	return (1);
}

t_list	*get_client(pid_t pid)
{
	t_list	*now;
	t_list	*new_client;
	t_data	*client_data;

	now = clients;
	while (now)
	{
		if (((t_data *)now->content)->cid == pid)
			return (now);
		now = now->next;
	}
	client_data = malloc(sizeof(t_data));
	if (!client_data)
		return (NULL);
	client_data->text = ft_strdup("");
	if (!client_data->text)
		return (free(client_data), NULL);
	client_data->bit_count = 0;
	client_data->cid = pid;
	client_data->symbol[0] = 0;
	client_data->symbol[1] = '\0';
	new_client = ft_lstnew(client_data);
	if (!new_client)
		return (free(client_data->text), free(client_data), NULL);
	ft_lstadd_front(&clients, new_client);
	return (new_client);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	t_list	*client;
	t_data	*data;

	(void)context;

	client = get_client(info->si_pid);
	if (!client)
		return;
	data = (t_data *)(client->content);
	data->time = 0;
	if (signum == SIGUSR1)
		data->symbol[0] |= (1 << (7 - data->bit_count));
	data->bit_count++;
	if (data->bit_count == 8)
	{
		if (!printing_behavior(&client))
			return;
		if (!client || !client->content)
			return;
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

void	dead_inactive_clients()
{
	t_list		*cli;
	t_list		*prev;
	t_data		*data;

	cli = clients;
	prev = NULL;
	while (cli)
	{
		data = (t_data *) cli->content;
		if (data->time > 150)
		{
			if (prev)
				prev->next = cli->next;
			else
				clients = cli->next;
			ft_putstr_fd("\nTimeout for PID ", 1);
			ft_putnbr_fd(data->cid, 1);
			write(1, "\n", 1);
			ft_lstdelone(cli, clear_content);
			if (prev)
				cli = prev->next;
			else
				cli = clients;
			continue;
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
	sigemptyset(&sa.sa_flags);
	server = getpid();
	ft_putstr_fd("Server PID ", 1);
	ft_putnbr_fd(server, 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		usleep(100000);
		cli = clients;
		while (cli)
		{
			((t_data *)(cli->content))->time++;
			cli = cli->next;
		}
		dead_inactive_clients();
		//pause();
	}
}
