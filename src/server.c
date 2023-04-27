/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/27 09:11:30 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/libft.h"

pid_t	client_pid;
t_char	g_char;

static void	receive_pid(void);
static void	receive_msg(void);

static void	init_char(void)
{
	g_char.current_bit = 0;
	g_char.parts = 0;
	return ;
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("%d\n", server_pid);
	while (true)
	{
		client_pid = 0;
		init_char();
		receive_pid();
		receive_msg();
	}
	return (0);
}

static void	receive_bit(int signum)
{
	if (signum == SIGUSR1)
		client_pid |= 1 << g_char.current_bit;
	else if (signum == SIGUSR2)
		client_pid &= ~(1 << g_char.current_bit);
	g_char.current_bit++;
	if (g_char.current_bit == 32)
	{
		ft_printf("client_pid: %d\n", client_pid);
	}
}

static void	receive_pid(void)
{
	init_char();
	signal(SIGUSR1, receive_bit);
	signal(SIGUSR2, receive_bit);
	while (g_char.current_bit < 32)
		pause();
}

static void	receive_char(int signum)
{
	if (signum == SIGUSR1)
		g_char.parts |= 1 << g_char.current_bit;
	else if (signum == SIGUSR2)
		g_char.parts &= ~(1 << g_char.current_bit);
	g_char.current_bit++;
	if (g_char.current_bit == 8)
	{
		if (g_char.parts == 4)
			return ;
		ft_putchar(g_char.parts);
		init_char();
	}
	return ;
}

static void	receive_msg(void)
{
	init_char();
	signal(SIGUSR1, receive_char);
	signal(SIGUSR2, receive_char);
	while (g_char.current_bit != 8 || g_char.parts != 4)
	// while (1)
	{
		// if (g_char.current_bit == 8 && g_char.parts == 4)
		// 	break ;
		pause();
	}
}
