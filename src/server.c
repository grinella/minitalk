#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char g_received_string[1024] = {0}; // Imposta una dimensione massima per la stringa

// Funzione per gestire i segnali SIGUSR1 e SIGUSR2
void signal_handler(int signo) {
    if (signo == SIGUSR1 || signo == SIGUSR2) {
        // Decodifica il bit ricevuto e aggiungi il carattere alla stringa
        static int g_received_bit_count = 0;
        static char g_received_char = 0;
        g_received_char |= (signo == SIGUSR2) << (7 - g_received_bit_count);
        g_received_bit_count++;
        if (g_received_bit_count == 8) {
            if (g_received_char == '\0') {
                // Fine della stringa, stampa la stringa ricevuta
                printf("Received: %s\n", g_received_string);
                fflush(stdout); // Assicura che l'output venga visualizzato immediatamente
                // Resetta i contatori
                g_received_bit_count = 0;
                g_received_char = 0;
                // Pulisci la stringa
                memset(g_received_string, 0, sizeof(g_received_string));
            } else {
                // Aggiungi il carattere alla stringa
                g_received_string[strlen(g_received_string)] = g_received_char;
                // Resetta i contatori
                g_received_bit_count = 0;
                g_received_char = 0;
            }
        }
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("Server PID: %d\n", getpid());

    while (1) {
        // Il server rimane attivo per ricevere i segnali
        usleep(100000); // Puoi regolare questa pausa se necessario
    }

    return 0;
}
