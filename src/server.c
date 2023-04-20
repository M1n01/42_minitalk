/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/20 20:51:19 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"

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

static void	receive_bit(int signum)
{
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
	return ;
}

static void	receive_msg(void)
{
	struct sigaction	s_sa;

	init_char();
	ft_bzero(&s_sa, sizeof(struct sigaction));
	s_sa.sa_handler = receive_bit;
	sigemptyset(&s_sa.sa_mask);
	sigaddset(&s_sa.sa_mask, SIGUSR1);
	sigaddset(&s_sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &s_sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &s_sa, NULL) == -1)
		exit(EXIT_FAILURE);
	// signal(SIGUSR1, receive_bit);
	// signal(SIGUSR2, receive_bit);
	while (1)
		pause();
}
