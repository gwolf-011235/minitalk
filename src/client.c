/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/04/22 11:23:22 by gwolf            ###   ########.fr       */
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

void	ft_convert_byte2bits(uint8_t c, pid_t server_pid)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		g_wait_for_response = true;
		bit = (c & (1 << i));
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i--;
		while (g_wait_for_response)
			;
	}
}

void	ft_send_to_server(char *input, pid_t server_pid)
{
	g_wait_for_response = true;
	kill(server_pid, SIGUSR1);
	sleep(1);
	if (g_wait_for_response)
	{
		ft_printf("Timeout. Please check PID\n");
		exit(1);
	}
	while (*input != '\0')
	{
		ft_convert_byte2bits(*input, server_pid);
		input++;
	}
}

pid_t	ft_validate_pid(char *pid)
{
	uint32_t	i;

	i = 0;
	while (pid[i])
	{
		if (!ft_isdigit(pid[i]))
		{
			return (0);
		}
		i++;
	}
	return (ft_atoi(pid));
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
	server_pid = ft_validate_pid(argv[1]);
	if (server_pid == 0)
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
