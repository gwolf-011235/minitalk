/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:49 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/25 09:10:54 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_convert_bin2dec(int sig, bool reset)
{
	static uint32_t	byte;
	static uint8_t	bit_count;

	if (reset)
	{
		byte = 0;
		bit_count = 0;
		return ;
	}
	if (sig == SIGUSR1)
		byte &= ~(1 << bit_count);
	else if	(sig == SIGUSR2)
		byte |= (1 << bit_count);
	else
		return;
	bit_count++;
	if (bit_count == 8)
	{
		write(0, &byte, 1);
		byte = 0;
		bit_count = 0;
	}
}

void	ft_handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	last_client;

	(void)ucontext;
	if (!last_client)
		last_client = info->si_pid;
	else if (last_client != info->si_pid)
	{
		ft_convert_bin2dec(sig, true);
		last_client = info->si_pid;
	}
	ft_convert_bin2dec(sig, false);
	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction	act;

	ft_printf("This is my pid: %d\n", getpid());
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = ft_handle_sigusr;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
