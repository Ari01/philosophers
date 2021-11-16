/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:40:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/16 18:19:20 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philosopher *philo, t_info *info)
{
	int		ret;
	float	time_diff;

	ret = 0;
	time_diff = get_timediff(philo->time_of_last_meal);
	if (info->time_to_die - time_diff <= 0.f)
	{
		pthread_mutex_lock(&info->mutex);
		philo->status = DIED;
		info->philosopher_died = 1;
		print_status(philo, info);
		pthread_mutex_unlock(&info->mutex);
		ret = 1;
	}
	return (ret);
}

void	rest(t_philosopher *philo, t_info *info)
{
	float	time_to_sleep;

	philo->status = SLEEPING;
	pthread_mutex_lock(&info->mutex);
	print_status(philo, info);
	pthread_mutex_unlock(&info->mutex);
	time_to_sleep = get_timediff(philo->time_of_last_meal) + info->time_to_sleep;
	if (time_to_sleep - info->time_to_die > 0.f)
	{
		time_to_sleep -= info->time_to_die;
		usleep(((unsigned long)time_to_sleep) * 1000);
	}
	else
		usleep((info->time_to_sleep - (unsigned long)get_timediff(philo->time_of_last_meal)) * 1000);
}

void	think(t_philosopher *philo, t_info *info)
{
	philo->status = THINKING;
	pthread_mutex_lock(&info->mutex);
	print_status(philo, info);
	pthread_mutex_unlock(&info->mutex);
}
