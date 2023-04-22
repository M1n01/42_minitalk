/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:35:23 by minabe            #+#    #+#             */
/*   Updated: 2023/04/22 15:51:44 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk_bonus.h"
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

unsigned char	decode_hamming(unsigned short encoded_data)
{
	unsigned short	error_bit;
	unsigned char	decoded;

	error_bit = 0;
	decoded = 0;
	error_bit |= ((encoded_data >> 11) ^ (encoded_data >> 9) ^ \
		(encoded_data >> 7) ^ (encoded_data >> 5) ^ \
		(encoded_data >> 3) ^ (encoded_data >> 1)) & 1;
	error_bit |= (((encoded_data >> 10) ^ (encoded_data >> 9) ^ \
		(encoded_data >> 6) ^ (encoded_data >> 5) ^ (encoded_data >> 2) ^ \
		(encoded_data >> 1)) & 1) << 1;
	error_bit |= (((encoded_data >> 8) ^ (encoded_data >> 7) ^ \
		(encoded_data >> 6) ^ (encoded_data >> 5) ^ (encoded_data)) & 1) << 2;
	error_bit |= (((encoded_data >> 4) ^ (encoded_data >> 3) ^ \
		(encoded_data >> 2) ^ (encoded_data >> 1) ^ (encoded_data)) & 1) << 3;
	if (error_bit)
		encoded_data ^= 1 << (12 - error_bit);
	decoded |= (encoded_data & 0b001000000000) >> 2;
	decoded |= (encoded_data & 0b000011100000) >> 1;
	decoded |= (encoded_data & 0b000000001111);
	return (decoded);
}

static void	receive_bit(int signum, siginfo_t *info, void *context)
{
	unsigned short	decoded;

	(void)context;
	if (signum == SIGUSR1)
		g_char.parts |= 1 << g_char.current_bit;
	else if (signum == SIGUSR2)
		g_char.parts &= ~(1 << g_char.current_bit);
	g_char.current_bit++;
	if (g_char.current_bit == 12)
	{
		decoded = decode_hamming(g_char.parts);
		ft_putchar_fd(decoded, 1);
		init_char();
	}
	usleep(10);
	if (info->si_pid != 0)
		kill(info->si_pid, SIGUSR1);
	else
		ft_printf("pid is 0\n");
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
