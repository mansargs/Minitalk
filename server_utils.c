/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:45:07 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/19 14:50:36 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	clear_content(void *content)
{
	if (!content)
		return ;
	free(((t_data *)content)->text);
}

static void	find_and_delete_client(t_list **client_ptr)
{
	t_list	*pre;
	t_list	*client;

	client = *client_ptr;
	if (!client)
		return ;
	if (client == g_clients)
		g_clients = g_clients->next;
	else
	{
		pre = g_clients;
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

static t_data	*initialize_content(pid_t pid)
{
	t_data	*client_data;

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
	return (client_data);
}

t_list	*get_client(const pid_t pid)
{
	t_list	*now;
	t_list	*new_client;
	t_data	*client_data;

	now = g_clients;
	while (now)
	{
		if (((t_data *)now->content)->cid == pid)
			return (now);
		now = now->next;
	}
	client_data = initialize_content(pid);
	if (!client_data)
		return (NULL);
	new_client = ft_lstnew(client_data);
	if (!new_client)
		return (free(client_data->text), free(client_data), NULL);
	ft_lstadd_front(&g_clients, new_client);
	return (new_client);
}
