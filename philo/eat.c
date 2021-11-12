/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 02:59:16 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/12 03:03:14 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philosopher *philo, t_info *info)
{
	int		ret;
	t_fork	*lf;
	t_fork	*rf;

	ret = 0;
	lf = philo->lf;
	rf = philo->rf;
	pthread_mutex_lock(&info->mutex);
	pthread_mutex_lock(&lf->mutex);
	pthread_mutex_lock(&rf->mutex);
	if (lf->status == AVAILABLE && rf->status == AVAILABLE)
	{
		philo->status = FORK;
		print_status(philo, info);
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
	rf->status = AVAILABLE;
	pthread_mutex_unlock(&lf->mutex);
	pthread_mutex_unlock(&rf->mutex);
	pthread_mutex_unlock(&info->mutex);
}

void	check_number_of_meal(t_philosopher *philo, t_info *info)
{
	if (info->number_of_eat != -1)
	{
		if (philo->number_of_eat == info->number_of_eat)
		{
			pthread_mutex_lock(&info->mutex);
			info->all_ate_count++;
			pthread_mutex_unlock(&info->mutex);
		}
	}
}

int	eat(t_philosopher *philo, t_info *info)
{
	if (take_forks(philo, info))
	{
		philo->status = EATING;
		pthread_mutex_lock(&info->mutex);
		print_status(philo, info);
		pthread_mutex_unlock(&info->mutex);
		usleep(info->time_to_eat * 1000);
		drop_forks(philo, info);
		philo->number_of_eat++;
		check_number_of_meal(philo, info);
		philo->time_of_last_meal = ft_gettime();
		return (1);
	}
	return (0);
}
