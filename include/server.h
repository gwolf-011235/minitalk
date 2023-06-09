/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:59:39 by gwolf             #+#    #+#             */
/*   Updated: 2023/04/22 11:07:30 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# include "ft_print.h"
# include "ft_fd.h"
# include "ft_char.h"

typedef struct s_msg
{
	pid_t		last_client;
	uint32_t	byte;
	uint8_t		bit_count;
}	t_msg;

void	ft_convert_bits2byte(int sig);
void	ft_handle_sigusr(int sig, siginfo_t *info, void *ucontext);

#endif
