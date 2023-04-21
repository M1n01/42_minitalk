/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:57:14 by minabe            #+#    #+#             */
/*   Updated: 2023/04/20 23:31:17 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "./ft_printf/ft_printf.h"

static int	check_sign(const char *str, size_t *i);
static void	error(char *str);

int	ft_atoi(const char *str)
{
	size_t		i;
	long long	nbr;
	int			sign;

	i = 0;
	while (('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ')
		i++;
	sign = check_sign(str, &i);
	nbr = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			error("Invalid PID.");
		if ((nbr * 10 + (str[i] - '0')) / 10 != nbr)
		{
			if (sign == 1)
				return (-1);
			if (sign == -1)
				return (0);
		}
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	nbr *= sign;
	return ((int)nbr);
}

static int	check_sign(const char *str, size_t *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static void	error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
	return ;
}
