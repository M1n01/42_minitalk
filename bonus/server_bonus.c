/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/27 07:22:59 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../include/libft.h"

t_char	g_char;

static void	init_char(void);
static void	receive_msg(void);

int	main(void)
{
	ft_printf("%d\n", getpid());
	receive_msg();
	return (0);
}

static void	init_char(void)
{
	g_char.current_bit = 0;
	g_char.parts = 0;
	return ;
}

static void	receive_bit(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		g_char.parts |= 1 << g_char.current_bit;
	else if (signum == SIGUSR2)
		g_char.parts &= ~(1 << g_char.current_bit);
	g_char.current_bit++;
	if (g_char.current_bit == 8)
	{
		ft_putchar_fd(g_char.parts, 1);
		init_char();
	}
	usleep(10);
	if (info->si_pid > 0)
		kill(info->si_pid, SIGUSR1);
	else
		ft_error("pid error\n");
	return ;
}

static void	receive_msg(void)
{
	struct sigaction	s_sa;

	init_char();
	ft_bzero(&s_sa, sizeof(struct sigaction));
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = receive_bit;
	sigaddset(&s_sa.sa_mask, SIGUSR1);
	sigaddset(&s_sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &s_sa, NULL) == -1 || \
		sigaction(SIGUSR2, &s_sa, NULL) == -1)
		ft_error("sigaction error\n");
	while (1)
		pause();
}
