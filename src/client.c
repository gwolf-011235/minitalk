/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/30 14:41:38 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	g_wait_for_response;

void	ft_handle_sigusr(int sig)
{
	(void)sig;
	g_wait_for_response = false;
	return ;
}

void	ft_convert_dec2bin(uint8_t dec, pid_t server_pid)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		g_wait_for_response = true;
		bit = (dec & (1 << i));
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		while (g_wait_for_response)
			;
	}
}

void	ft_send_to_server(char *input, pid_t server_pid)
{
	while (*input != '\0')
	{
		ft_convert_dec2bin(*input, server_pid);
		input++;
	}
}

bool	ft_is_valid_pid(char *pid)
{
	uint32_t	i;

	i = 0;
	while (pid[i])
	{
		if (!ft_isdigit(pid[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	struct sigaction	act;

	if (argc != 3)
	{
		ft_printf("Please enter PID and then a string\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (!ft_is_valid_pid(argv[1]))
	{
		ft_printf("Please enter a valid PID\n");
		return (1);
	}
	act.sa_handler = ft_handle_sigusr;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		exit(1);
	ft_send_to_server(argv[2], server_pid);
}
