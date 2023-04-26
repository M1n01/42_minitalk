/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:20 by minabe            #+#    #+#             */
/*   Updated: 2023/04/27 07:59:12 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/libft.h"

static void	send_pid(pid_t server_pid, pid_t client_pid);

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	pid_t	client_pid;


	if (argc == 1)
		ft_error("usage: ./client [pid] [message]\n");
	server_pid = ft_atoi(argv[1]);
	client_pid = getpid();
	send_pid(server_pid, client_pid);
	return (0);
}

void	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < 32)
	{
		if (client_pid & (1 << i))
			status = kill(server_pid, SIGUSR1);
		else
			status = kill(server_pid, SIGUSR2);
		if (status == -1)
			ft_error("kill failed\n");
		usleep(100);
		i++;
	}
	ft_printf("%d\n", client_pid);
}
