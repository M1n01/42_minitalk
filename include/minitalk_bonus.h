/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:28:54 by minabe            #+#    #+#             */
/*   Updated: 2023/04/22 14:51:21 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sysexits.h>
# define EOT 4

typedef struct s_char
{
	int				current_bit;
	unsigned short	parts;
}				t_char;

#endif