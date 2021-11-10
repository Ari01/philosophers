/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:40:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/10 01:39:39 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philosopher *philo, t_info *info)
{
	int				ret;
	float			time_diff;
	unsigned long	time;

	ret = 0;
	time = ft_gettime();
	if (!time)
		return (1);
	time_diff = get_timediff(time, philo->time_of_last_meal);
	//time_diff = (time - philo->time_of_last_meal) / 1000;
	pthread_mutex_lock(&info->mutex);
	printf("thread %d\n", philo->number);
	printf("time diff = %ld - %ld = %f\n", time, philo->time_of_last_meal, time_diff);
	pthread_mutex_unlock(&info->mutex);
	if (info->time_to_die - time_diff <= 0.f)
	{
		philo->status = DIED;
		pthread_mutex_lock(&info->mutex);
		info->philosopher_died = 1;
		print_status(time, *philo);
		pthread_mutex_unlock(&info->mutex);
		ret = 1;
	}
	return (ret);
}

void	take_fork(t_fork *fork, t_philosopher *philo, t_info *info)
{
	unsigned long	time;

	time = ft_gettime();
	if (time && fork->status == AVAILABLE)
	{
		pthread_mutex_lock(&info->mutex);
		pthread_mutex_lock(&fork->mutex);
		philo->status = FORK;
		print_status(time, *philo);
		fork->status = BUSY;
		pthread_mutex_unlock(&fork->mutex);
		pthread_mutex_unlock(&info->mutex);
	}
}

void	eat(t_philosopher *philo, t_info *info)
{
	t_fork			*lf;
	t_fork			*rf;
	unsigned long	time;

	lf = &info->forks[philo->left];
	rf = &info->forks[philo->right];
	if (philo->status == THINKING)
	{
		if (lf->status == AVAILABLE && rf->status == AVAILABLE)
		{
			take_fork(lf, philo, info);
			take_fork(rf, philo, info);
			philo->status = EATING;
			time = ft_gettime();
			if (time)
				philo->time_of_last_meal = time + info->time_to_eat;
		}
	}
}
