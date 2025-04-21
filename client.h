/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:14:50 by mansargs          #+#    #+#             */
/*   Updated: 2025/04/21 22:14:51 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include "libft/libft.h"

extern volatile sig_atomic_t	g_stop;

void	setup_handler(void);

#endif
