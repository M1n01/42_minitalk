/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/17 21:58:46 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"

t_char	g_char;

static void	init_char(void);
static void	recieve_bit(int signal);

int	main(void)
{
	pid_t	my_pid;

	init_char();
	my_pid = getpid();
	ft_printf("%d\n", my_pid);
	signal(SIGUSR1, recieve_bit);
	signal(SIGUSR2, recieve_bit);
	while (1)
		pause();
	return (0);
}

static void	init_char(void)
{
	g_char.count = 0;
	g_char.parts = 0;
	return ;
}

static void	recieve_bit(int signum)
{
	if (signum == SIGUSR1)
		g_char.parts += (0b00000001 << g_char.count);
	if (g_char.count == 7)
	{
		ft_printf("%c", g_char.parts);
		init_char();
		return ;
	}
	g_char.count++;
	return ;
}
