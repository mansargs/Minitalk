/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_inactive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:08:21 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/21 22:14:27 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	print_timeout_and_clear(t_list *cli)
{
	write(1, "\nTimeout for PID ", 17);
	ft_putnbr_fd(((t_data *)cli->content)->cid, 1);
	write(1, "\n", 1);
	usleep(180);
	ft_lstdelone(cli, clear_content);
}

void	dead_inactive_clients(void)
{
	t_list		*cli;
	t_list		*prev;

	cli = g_clients;
	prev = NULL;
	while (cli)
	{
		if (((t_data *)cli->content)->time > 40)
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
