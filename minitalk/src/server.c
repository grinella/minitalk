/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:27:44 by grinella          #+#    #+#             */
/*   Updated: 2023/10/10 19:24:18 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione per gestire i segnali SIGUSR1 e SIGUSR2
void	signal_handler(int signo)
{
	static int	g_received_bit_count = 0;
	static char	g_received_char = 0;

	if (signo == SIGUSR1 || signo == SIGUSR2)
	{
		g_received_char |= (signo == SIGUSR2) << (7 - g_received_bit_count);
		g_received_bit_count++;
		if (g_received_bit_count == 8)
		{
			if (g_received_char == '\0')
			{
				fflush(stdout);
				write(1, "\n", 1);
				g_received_bit_count = 0;
				g_received_char = 0;
			}
			else
			{
				printf("%c", g_received_char);
				g_received_bit_count = 0;
				g_received_char = 0;
			}
		}
	}
}

// dimensione massima stringa: string_max[1024]
int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (1)
	{
		usleep(100000);
	}
	return (0);
}
// Il server rimane attivo per ricevere i segnali: usleep(100000)

/*
La funzione inizia dichiarando due variabili statiche
g_received_bit_count e g_received_char.

Queste variabili vengono utilizzate per raccogliere
i bit ricevuti e costruire una stringa.

Viene dichiarato un array di caratteri string_max
di dimensione 1024, che verrà utilizzato per raccogliere
la stringa completa ricevuta.

La funzione controlla se il segnale signo è uguale
a SIGUSR1 o SIGUSR2.
Se il segnale è SIGUSR2, la funzione aggiunge un bit
1 alla variabile g_received_char in base alla posizione 
g_received_bit_count.

La variabile g_received_bit_count tiene traccia dei bit
ricevuti fino a quando non raggiunge 8 
(che rappresenta un carattere completo).

Quando g_received_bit_count raggiunge 8, significa che
è stato ricevuto un carattere completo. 
La funzione verifica se il carattere è il terminatore
nullo '\0', che indica la fine della stringa.

Se il carattere è '\0', la funzione stampa la stringa
ricevuta e la resetta. In caso contrario, aggiunge il 
carattere alla stringa string_max.
*/