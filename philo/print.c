/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:09:09 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/11 01:28:50 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *s)
{
	write(1, s, ft_strlen(s));
}

void	print_number(int n)
{
	unsigned int	unbr;
	char			c;

	unbr = n;
	if (n < 0)
	{
		write(1, "-", 1);
		unbr = -n;
	}
	if (unbr / 10 == 0)
	{
		c = unbr + '0';
		write(1, &c, 1);
	}
	else
	{
		print_number(unbr / 10);
		c = unbr % 10 + '0';
		write(1, &c, 1);
	}
}

void	print_info(t_info *info)
{
	print_msg("current philosopher = ");
	print_number(info->current_philosopher);
	print_msg("\n");
	print_msg("nphilo = ");
	print_number(info->number_of_philosophers);
	print_msg(", ttd = ");
	print_number(info->time_to_die);
	print_msg(", tte = ");
	print_number(info->time_to_eat);
	print_msg(", tts = ");
	print_number(info->time_to_sleep);
	print_msg(", neat = ");
	print_number(info->number_of_eat);
	print_msg(", ate count = ");
	print_number(info->all_ate_count);
	print_msg(", philosopher died = ");
	print_number(info->philosopher_died);
	print_msg("\n");
}

void	print_status(float time, t_philosopher philo)
{
	print_number((int)time);
	print_msg(" ");
	print_number(philo.number);
	print_msg(" ");
	if (philo.status == DIED)
		print_msg("died");
	else if (philo.status == FORK)
		print_msg("has taken a fork");
	else if (philo.status == EATING)
		print_msg("is eating");
	else if (philo.status == SLEEPING)
		print_msg("is sleeping");
	else if (philo.status == THINKING)
		print_msg("is thinking");
	print_msg("\n");
}
