/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:49 by gwolf             #+#    #+#             */
/*   Updated: 2023/04/22 11:13:57 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_msg	g_msg;

void	ft_convert_bits2byte(int sig)
{
	if (sig == SIGUSR1)
		g_msg.byte = g_msg.byte << 1;
	else if (sig == SIGUSR2)
		g_msg.byte = (g_msg.byte << 1) | 1;
	else
		return ;
	g_msg.bit_count++;
	if (g_msg.bit_count == 8)
	{
		write(0, &g_msg.byte, 1);
		g_msg.byte = 0;
		g_msg.bit_count = 0;
	}
}

void	ft_handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_msg.last_client != info->si_pid)
	{
		g_msg.last_client = info->si_pid;
		g_msg.byte = 0;
		g_msg.bit_count = 0;
	}
	else
		ft_convert_bits2byte(sig);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("This is my pid: %d\n", getpid());
	act.sa_sigaction = ft_handle_sigusr;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		exit(1);
	while (1)
		pause();
}
