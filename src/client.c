/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:20 by minabe            #+#    #+#             */
/*   Updated: 2023/04/20 14:44:45 by minabe           ###   ########.fr       */
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
		ft_printf("Usage: ./client [server-pid] [message]");
		exit(EX_USAGE);
	}
	my_pid = ft_atoi(av[1]);
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
		if (uc & (1 << current_bit))
			status = kill(my_pid, SIGUSR1);
		else
			status = kill(my_pid, SIGUSR2);
		if (status == -1)
			error("Invalid PID.");
		usleep(500);
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

static void	error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
	return ;
}
