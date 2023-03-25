/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/25 11:32:16 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_handle_sigusr(int sig)
{
	(void)sig;
	return ;
}

void	ft_convert_dec2bin(uint8_t dec, pid_t server_pid)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = (dec & (1 << i));
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		pause();
	}
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;
	struct sigaction	act;
	char				*input;

	if (argc != 3)
	{
		ft_printf("Please enter pid and then a string\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	input = argv[2];
	act.sa_handler = ft_handle_sigusr;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		exit(1);
	while (*input != '\0')
	{
		ft_convert_dec2bin(*input, server_pid);
		input++;
	}
}
