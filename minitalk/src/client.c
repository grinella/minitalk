/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:30:49 by grinella          #+#    #+#             */
/*   Updated: 2023/10/10 18:10:00 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
PER INVIARE UN SINGOLO CARATTERE TRAMITE SEGNALI
Questa funzione (ft_send_char) invia il carattere `c` al processo
identificato da `pid` utilizzando i segnali SIGUSR1 e SIGUSR2.
I bit del carattere vengono inviati uno alla volta, con un bit per ogni segnale.
Se il bit è 1, viene inviato SIGUSR2; se è 0, viene inviato SIGUSR1.
La funzione attende brevemente tra l'invio di ciascun bit.
*/

void	ft_send_char(int pid, char c)
{
	int	bit;

	bit = 128;
	while (bit > 0)
	{
		if (c & bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit /= 2;
		usleep(100);
	}
}

/*

*/
void	ft_send_str(int pid, char *str)
{
	while (*str)
	{
		ft_send_char(pid, *str);
		str++;
	}
	ft_send_char(pid, '\0');
}

int	main(int argc, char *argv[])
{
	int	server_pid;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <string>\n", argv[0]);
		return (1);
	}
	server_pid = atoi(argv[1]);
	ft_send_str(server_pid, argv[2]);
	return (0);
}
