/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:49 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/24 21:52:14 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

void	ft_handle_sig(int sig)
{
	if (sig == SIGUSR1)
		printf("received 1\n");
	else if	(sig == SIGUSR2)
		printf("received 2\n");
}

int main(void)
{
	struct sigaction	sa;

	printf("This is my pid: %d", getpid());
	sa.sa_handler = ft_handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pause();
}
