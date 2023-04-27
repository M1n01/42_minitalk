/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:20 by minabe            #+#    #+#             */
/*   Updated: 2023/04/27 08:48:20 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/libft.h"

static void	send_pid(pid_t server_pid, pid_t client_pid);
static void	send_msg(pid_t my_pid, char *msg);

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	pid_t	client_pid;

	if (argc != 3)
		ft_error("Usage: ./client [server-pid] [message]");
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 100 || 99998 < server_pid)
		ft_error("Invalid PID. Please enter a number between 100 and 99998.");
	client_pid = getpid();
	send_pid(server_pid, client_pid);
	send_msg(server_pid, argv[2]);
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

static void	send_char(pid_t my_pid, char c)
{
	unsigned char	uc;
	size_t			current_bit;
	int				status;

	uc = (unsigned char)c;
	current_bit = 0;
	while (current_bit < 8)
	{
		usleep(500);
		if (uc & (1 << current_bit))
			status = kill(my_pid, SIGUSR1);
		else
			status = kill(my_pid, SIGUSR2);
		if (status == -1)
			ft_error("Invalid PID.");
		current_bit++;
	}
	return ;
}

static void	send_msg(pid_t my_pid, char *msg)
{
	size_t				i;

	i = 0;
	while (msg[i] != '\0')
	{
		send_char(my_pid, msg[i]);
		i++;
	}
	send_char(my_pid, 4);
	return ;
}