/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/22 19:46:07 by minabe           ###   ########.fr       */
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
	g_char.current_bit++;
	if (g_char.current_bit == 12)
	{
		ft_putchar_fd(g_char.parts, 1);
		init_char();
	}
	return ;
}

static void	receive_msg(void)
{
	init_char();
	if (signal(SIGUSR1, receive_bit) == SIG_ERR \
		|| signal(SIGUSR2, receive_bit) == SIG_ERR)
		ft_error("signal error\n");
	while (1)
		pause();
}
