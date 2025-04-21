/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:14:40 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/21 22:14:41 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_stop;

static int	valid_pid(const char *pid)
{
	if (!pid)
		return (0);
	while (*pid == ' ')
		++pid;
	if (*pid == '+' || *pid == '-')
		++pid;
	while (*pid)
	{
		if (!ft_isdigit(*pid))
			return (0);
		++pid;
	}
	return (1);
}

static void	send_bit(const pid_t server, const char bit)
{
	if (bit == 1)
		kill (server, SIGUSR1);
	else
		kill (server, SIGUSR2);
	if (errno == ESRCH)
	{
		ft_putstr_fd("Unfortunately, the connection to the "
			"server was lost.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	send_symbol(const pid_t server, const char c)
{
	int		i;
	char	bit;

	i = 8;
	while (--i >= 0)
	{
		bit = (c >> i) & 1;
		g_stop = 0;
		while (!g_stop)
		{
			send_bit(server, bit);
			usleep(100000);
		}
	}
}

static void	send_message(const pid_t server, const char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		send_symbol(server, *str);
		++str;
	}
	send_symbol(server, '\0');
}

int	main(int argc, char *argv[])
{
	pid_t	server;

	if (argc != 3 || !valid_pid(argv[1]))
	{
		ft_putstr_fd("Incorrect arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	server = ft_atoi(argv[1]);
	kill(server, 0);
	if (errno == ESRCH)
	{
		ft_putstr_fd("Don't have ", STDERR_FILENO);
		ft_putnbr_fd(server, STDERR_FILENO);
		ft_putendl_fd(" PID", STDERR_FILENO);
	}
	else if (errno == EPERM)
		ft_putstr_fd("Don't have permission access\n", STDERR_FILENO);
	else
	{
		setup_handler();
		send_message(server, argv[2]);
	}
	return (EXIT_SUCCESS);
}
