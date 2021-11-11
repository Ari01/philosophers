/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:40:50 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/11 02:07:51 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philosopher *philo, t_info *info)
{
	int		ret;
	float	time_diff;

	ret = 0;
	time_diff = get_timediff(philo->time_of_last_meal);
	if (time_diff >= info->time_to_die)
	{
		philo->status = DIED;
		info->philosopher_died = 1;
		print_status(time_diff, *philo);
		ret = 1;
	}
	return (ret);
}

int	take_forks(t_philosopher *philo, t_info *info)
{
	float	timediff;
	int		ret;
	t_fork	*lf;
	t_fork	*rf;

	ret = 0;
	lf = philo->lf;
	rf = philo->rf;
	timediff = get_timediff(info->time_start);
	pthread_mutex_lock(&info->mutex);
	pthread_mutex_lock(&lf->mutex);
	pthread_mutex_lock(&rf->mutex);
	if (lf->status == AVAILABLE && rf->status == AVAILABLE)
	{
		philo->status = FORK;
		print_status(timediff, *philo);
		lf->status = BUSY;
		rf->status = BUSY;
		ret = 1;
	}
	pthread_mutex_unlock(&lf->mutex);
	pthread_mutex_unlock(&rf->mutex);
	pthread_mutex_unlock(&info->mutex);
	return (ret);
}

void	drop_forks(t_philosopher *philo, t_info *info)
{
	t_fork	*lf;
	t_fork	*rf;

	lf = philo->lf;
	rf = philo->rf;
	pthread_mutex_lock(&info->mutex);
	pthread_mutex_lock(&lf->mutex);
	pthread_mutex_lock(&rf->mutex);
	lf->status = AVAILABLE;
	lf->status = AVAILABLE;
	pthread_mutex_unlock(&lf->mutex);
	pthread_mutex_unlock(&rf->mutex);
	pthread_mutex_unlock(&info->mutex);
}

void	eat(t_philosopher *philo, t_info *info)
{
	float	timediff;

	if (take_forks(philo, info))
	{
		philo->status = EATING;
		timediff = get_timediff(info->time_start);
		pthread_mutex_lock(&info->mutex);
		print_status(timediff, *philo);
		pthread_mutex_unlock(&info->mutex);
		usleep(info->time_to_eat * 1000);
		drop_forks(philo, info);
		philo->time_of_last_meal = ft_gettime();
		philo->status = SLEEPING;
		timediff = get_timediff(info->time_start);
		pthread_mutex_lock(&info->mutex);
		print_status(timediff, *philo);
		pthread_mutex_unlock(&info->mutex);
		usleep(info->time_to_sleep * 1000);
		philo->status = THINKING;
		timediff = get_timediff(info->time_start);
		pthread_mutex_lock(&info->mutex);
		print_status(timediff, *philo);
		pthread_mutex_unlock(&info->mutex);
	}
}
