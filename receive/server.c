/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:27:35 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/15 21:30:13 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_list	*clients = NULL;



void	clear_content(void *content)
{
	free(((t_data *)(content))->text);
}



int	printing_behavior(t_list *client)
{
	char	*temp;
	t_list	*next;

	if (client == clients)
	{
		if (!ft_strncmp((((t_data *)(client->content))->text), "", 1))
		{
			ft_putstr_fd(((t_data *)(client->content))->text, 1);
			clear_content(client->content);
			((t_data *)(client->content))->text = ft_strdup("");
		}
		if (((t_data *)(client->content))->symbol[0] == '\0')
		{
			ft_putchar_fd('\n', 1);
			next = clients->next;
			ft_lstdelone(client, clear_content);
			clients = next;
		}
		else
			ft_putchar_fd(((t_data *)(client->content))->symbol[0], 1);
	}
	else
	{
		temp = ft_strjoin(((t_data *)(client->content))->symbol, ((t_data *)(client->content))->text);
		if (!temp)
			return (0);
		free(((t_data *)(client->content))->text);
		((t_data *)(client->content))->text = temp;
	}
	return (1);
}




t_list	*get_client(pid_t pid)
{
	t_list	*now;
	t_list	*new_client;

	now = clients;
	while(now)
	{
		if (((t_data *)(now->content))->cid == pid)
			return (now);
		now = now->next;
	}
	t_data *client_data = (t_data *)malloc(sizeof(t_data));
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
		return (NULL);
	ft_lstadd_front(&clients, new_client);
	return (new_client);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	t_list	*client;

	(void) context;
	client = get_client(info->si_pid);
	if (!client)
		return ;
	if (signum == SIGUSR1)
		((t_data *)(client->content))->symbol[0] |= (1 << (7 - ((t_data *)(client->content))->bit_count));
	++((t_data *)(client->content))->bit_count;
	if (((t_data *)(client->content))->bit_count == 8)
	{
		if (!printing_behavior(client))
			return ;
		((t_data *)(client->content))->bit_count = 0;
		((t_data *)(client->content))->symbol[0] = 0;
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
