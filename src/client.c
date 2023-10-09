#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
