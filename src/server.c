/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:49 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/24 22:40:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_handle_sig(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("received 1\n");
	else if	(sig == SIGUSR2)
		ft_printf("received 2\n");
}

int main(void)
{
	struct sigaction	sa;

	ft_printf("This is my pid: %d", getpid());
	sa.sa_handler = ft_handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pause();
}
