/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/24 22:41:12 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int argc, char *argv[])
{
	int pid;

	if (argc != 3)
	{
		ft_printf("Please enter pid and then a string\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	kill(pid, SIGUSR1);
}