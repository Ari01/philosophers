/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:33:14 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/10 00:15:06 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_lr_philosophers(t_philosopher *philo, t_info *info)
{
	if (philo->number == 1)
		philo->left = info->number_of_philosophers;
	else
		philo->left = philo->number - 1;
	if (philo->number == info->number_of_philosophers)
		philo->right = 1;
	else
		philo->right = philo->number + 1;
}

int	init_philosopher(t_philosopher *philo, t_info *info)
{
	pthread_mutex_lock(&info->mutex);
	philo->number = info->current_philosopher;
	info->current_philosopher++;
	pthread_mutex_unlock(&info->mutex);
	set_lr_philosophers(philo, info);
	philo->status = THINKING;
	philo->number_of_eat = 0;
	philo->time_of_last_meal = info->time_start;
	if (!philo->time_of_last_meal)
		return (0);
	return (1);
}

int	end_simulation(t_philosopher *philo, t_info *info)
{
	int				ret;

	ret = 0;
	if (info->all_ate_count == info->number_of_philosophers)
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
	}
}
