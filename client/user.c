/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:34:18 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/17 18:10:48 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.h"

volatile sig_atomic_t stop;

int	valid_pid(const char *pid)
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
			return 0;
		++pid;
	}
	return (1);
}

void	reply_from_server(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;

	if (sig == SIGUSR1)
		stop = 1;
	else if(sig == SIGUSR2)
	{
		ft_putstr_fd("\nThe text has been successfully delivered.\n", 1);
		exit(EXIT_SUCCESS);
	}
}

void setup_handler()
{
	struct sigaction sa;

	sa.sa_sigaction = reply_from_server;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

void	send_bit(const pid_t server,const char bit)
{

	if (bit == 1)
		kill (server, SIGUSR1);
	else
		kill (server, SIGUSR2);
	if (errno == ESRCH)
	{
		ft_putstr_fd("Unfortunately, the connection to the server was lost.\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	send_symbol(const pid_t server,const char c)
{
	int		i;
	char	bit;

	i = 8;
	while (--i >= 0)
	{
		bit = (c >> i) & 1;
		stop = 0;
		while (!stop)
		{
			send_bit(server, bit);
			usleep(100000);
		}
	}
}

void	send_message(const pid_t server,const char *str)
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

int main (int argc, char *argv[])
{
	pid_t	server;

	if (argc != 3 || !valid_pid(argv[1]))
	{
		ft_putstr_fd("Error message\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	server = ft_atoi(argv[1]);
	kill(server, 0);
	if (errno == ESRCH)
		printf("Don't have %d PID\n", server);
	else if (errno == EPERM)
		printf("We haven't permission access\n");
	else
	{
		setup_handler();
		send_message(server ,argv[2]);
	}
	return (0);
}
