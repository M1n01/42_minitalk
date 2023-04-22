/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:20 by minabe            #+#    #+#             */
/*   Updated: 2023/04/22 14:40:30 by minabe           ###   ########.fr       */
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
		error("Usage: ./client [server-pid] [message]");
	my_pid = ft_atoi(av[1]);
	if (my_pid < 100 || 99998 < my_pid)
		error("Invalid PID. Please enter a number between 100 and 99998.");
	send_msg(my_pid, av[2]);
	return (0);
}

static unsigned short	encode_hamming(unsigned char data)
{
	unsigned short	encoded;

	encoded = 0;
	encoded |= (data & 0b10000000) << 2;
	encoded |= (data & 0b01110000) << 1;
	encoded |= (data & 0b00001111);
	encoded |= (encoded ^ (encoded << 2) ^ (encoded << 4) ^ (encoded << 6) ^ \
		(encoded << 8) ^ (encoded << 10)) & 0b100000000000;
	encoded |= (encoded ^ (encoded << 1) ^ (encoded << 4) ^ (encoded << 5) ^ \
		(encoded << 8) ^ (encoded << 9)) & 0b010000000000;
	encoded |= (encoded ^ (encoded << 1) ^ (encoded << 2) ^ (encoded << 3) ^ \
		(encoded << 8)) & 0b000100000000;
	encoded |= (encoded ^ (encoded << 1) ^ (encoded << 2) ^ (encoded << 3) ^ \
		(encoded << 4)) & 0b000000010000;
	return (encoded);
}

static void	send_char(pid_t my_pid, char c)
{
	unsigned char	uc;
	size_t			current_bit;
	unsigned short	encoded;
	int				status;

	uc = (unsigned char)c;
	encoded = encode_hamming(uc);
	current_bit = 0;
	while (current_bit < 12)
	{
		usleep(100);
		if (encoded & (1 << current_bit))
			status = kill(my_pid, SIGUSR1);
		else
			status = kill(my_pid, SIGUSR2);
		if (status == -1)
			error("Invalid PID.");
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
