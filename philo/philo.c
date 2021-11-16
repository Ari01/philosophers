/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:33:14 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/16 17:47:30 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	set_lr_philosophers(t_philosopher philo, t_info *info)
{
	int	left;
	int	right;

	if (philo.number == info->number_of_philosophers)
		right = 0;
	else
		right = philo.number;
	left = philo.number - 1;
	philo.lf = &info->forks[left];
	philo.rf = &info->forks[right];
	return (philo);
}

t_philosopher	init_philosopher(t_info *info)
{
	t_philosopher	philo;

	pthread_mutex_lock(&info->mutex);
	philo.number = info->current_philosopher;
	info->current_philosopher++;
	pthread_mutex_unlock(&info->mutex);
	philo = set_lr_philosophers(philo, info);
	philo.status = THINKING;
	philo.number_of_eat = 0;
	philo.time_of_last_meal = info->time_start;
	return (philo);
}

int	end_simulation(t_philosopher *philo, t_info *info)
{
	int				ret;

	ret = 0;
	if (info->all_ate_count >= info->number_of_philosophers)
		ret = 1;
	else if (info->philosopher_died)
		ret = 1;
	else if (die(philo, info))
		ret = 1;
	return (ret);
}

void	simulate(t_philosopher *philo, t_info *info)
{
	while (!end_simulation(philo, info))
	{
		if (philo->status == THINKING)
			eat(philo, info);
		else if (philo->status == EATING)
			rest(philo, info);
		else if (philo->status == SLEEPING)
			think(philo, info);
	}
}
