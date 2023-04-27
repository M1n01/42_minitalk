/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/27 12:04:35 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/libft.h"

t_server	g_server;

static void	receive_pid(void);
static void	receive_msg(void);

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("%d\n", server_pid);
	while (true)
	{
		receive_pid();
		receive_msg();
	}
	return (0);
}

static void	init_char(void)
{
	g_server.current_bit = 0;
	g_server.binary = 0;
	return ;
}

static void	receive_bit(int signum)
{
	if (signum == SIGUSR1)
		g_server.binary |= 1 << g_server.current_bit;
	else if (signum == SIGUSR2)
		g_server.binary &= ~(1 << g_server.current_bit);
	g_server.current_bit++;
	if (g_server.current_bit == 32)
	{
		g_server.client_pid = g_server.binary;
		return ;
	}
}

static void	receive_pid(void)
{
	init_char();
	g_server.client_pid = 0;
	signal(SIGUSR1, receive_bit);
	signal(SIGUSR2, receive_bit);
	while (g_server.current_bit < 32)
		pause();
}

static void	receive_char(int signum)
{
	int	status;

	if (signum == SIGUSR1)
		g_server.binary |= 1 << g_server.current_bit;
	else if (signum == SIGUSR2)
		g_server.binary &= ~(1 << g_server.current_bit);
	g_server.current_bit++;
	if (g_server.current_bit == 8)
	{
		if (g_server.binary == 4)
			return ;
		ft_putchar((unsigned char)g_server.binary);
		init_char();
	}
	usleep(100);
	status = kill(g_server.client_pid, SIGUSR1);
	if (status == -1)
		ft_error("kill error\n");
	return ;
}

static void	receive_msg(void)
{
	struct sigaction	s_sa;

	init_char();
	ft_bzero(&s_sa, sizeof(struct sigaction));
	s_sa.sa_handler = receive_char;
	s_sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &s_sa, NULL) == -1 || \
		sigaction(SIGUSR2, &s_sa, NULL) == -1)
		ft_error("sigaction error\n");
	while (g_server.current_bit != 8 || g_server.binary != 4)
		pause();
}
