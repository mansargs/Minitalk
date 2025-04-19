/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:21:35 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/19 15:37:25 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct s_server
{
	pid_t				cid;
	char				symbol[2];
	char				bit_count;
	char				*text;
	unsigned int		time;
}						t_data;

extern t_list	*g_clients;

void	clear_content(void *content);
t_list	*get_client(const pid_t pid);
int		printing_behavior(t_list **client_ptr);

#endif
