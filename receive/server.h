/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:21:35 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/17 11:48:22 by lenovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include "../Libft/libft.h"

typedef struct s_server
{
	pid_t				cid;
	char				symbol[2];
	char				bit_count;
	char				*text;
	unsigned int		time;
}						t_data;

#endif
