/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:20 by minabe            #+#    #+#             */
/*   Updated: 2023/04/17 21:58:34 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"

static void	send_msg(pid_t my_pid, char *msg);
static void	error(char *str);

int	main(int ac, char *av[])
{
	pid_t	my_pid;

	if (ac != 3)
	{
		ft_printf("usage: ./client [server-pid] [message]");
		exit(EX_USAGE);
	}
	my_pid = ft_atoi(av[1]);
	send_msg(my_pid, av[2]);
	return (0);
}

static void	send_msg(pid_t my_pid, char *msg)
{
	size_t	i;
	size_t	count;
	int		status;

	i = 0;
	while (msg[i] != '\0')
	{
		count = 0;
		while (count < 8)
		{
			if ((msg[i] >> count) & 0b00000001)
				status = kill(my_pid, SIGUSR1);
			else
				status = kill(my_pid, SIGUSR2);
			if (status == -1)
				error("Invalid PID.");
			count++;
			usleep(500);
		}
		i++;
	}
	return ;
}

static void	error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
	return ;
}
