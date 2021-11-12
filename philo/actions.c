/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:40:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/12 03:00:23 by dchheang         ###   ########.fr       */
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
		philo->status = DIED;
		info->philosopher_died = 1;
		print_status(philo, info);
		ret = 1;
	}
	return (ret);
}

void	rest(t_philosopher *philo, t_info *info)
{
	philo->status = SLEEPING;
	pthread_mutex_lock(&info->mutex);
	print_status(philo, info);
	pthread_mutex_unlock(&info->mutex);
	usleep(info->time_to_sleep * 1000);
}

void	think(t_philosopher *philo, t_info *info)
{
	philo->status = THINKING;
	pthread_mutex_lock(&info->mutex);
	print_status(philo, info);
	pthread_mutex_unlock(&info->mutex);
}
