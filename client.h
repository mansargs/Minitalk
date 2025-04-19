/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenovo <lenovo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 00:34:40 by lenovo            #+#    #+#             */
/*   Updated: 2025/04/19 15:17:53 by lenovo           ###   ########.fr       */
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
