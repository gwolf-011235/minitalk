/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:00:11 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/30 14:43:27 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define _XOPEN_SOURCE 700
# define _DEFAULT_SOURCE

# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# include "ft_print.h"

bool	ft_is_valid_pid(char *pid);
void	ft_send_to_server(char *input, pid_t server_pid);
void	ft_convert_dec2bin(uint8_t dec, pid_t server_pid);
void	ft_handle_sigusr(int sig);

#endif
