/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:56:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/24 21:57:04 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Please enter pid and then a string\n");
		return (1);
	}
	kill(

}
