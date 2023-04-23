/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:20 by minabe            #+#    #+#             */
/*   Updated: 2023/04/23 12:49:49 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"

static void	send_msg(pid_t my_pid, char *msg);

int	main(int ac, char *av[])
{
	pid_t	my_pid;

	if (ac != 3)
		ft_error("Usage: ./client [server-pid] [message]");
	my_pid = ft_atoi(av[1]);
	if (my_pid < 100 || 99998 < my_pid)
		ft_error("Invalid PID. Please enter a number between 100 and 99998.");
	send_msg(my_pid, av[2]);
	return (0);
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
		usleep(100);
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
	size_t	i;

	i = 0;
	while (msg[i] != '\0')
	{
		send_char(my_pid, msg[i]);
		i++;
	}
	return ;
}
