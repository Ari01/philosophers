/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 02:59:16 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/16 18:03:05 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_queue(t_list *queue, int n)
{
	if (!queue)
		return (1);
	if (queue->value == n)
		return (1);
	return (0);
}

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
		if (check_queue(lf->queue, philo->number)
			&& check_queue(rf->queue, philo->number))
		{
			philo->status = FORK;
			print_status(philo, info);
			lf->status = BUSY;
			rf->status = BUSY;
			ret = 1;
			if (lf->queue)
				ft_lstremove(&lf->queue, philo->number);
			if (rf->queue)
				ft_lstremove(&rf->queue, philo->number);
		}
	}
	else
	{
		if (!ft_lstfind(lf->queue, philo->number))
			ft_lstadd_back(&lf->queue, ft_lstnew(philo->number));
		if (!ft_lstfind(rf->queue, philo->number))
			ft_lstadd_back(&rf->queue, ft_lstnew(philo->number));
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
	if (info->number_of_philosophers == 1)
		return (0);
	if (take_forks(philo, info))
	{
		philo->status = EATING;
		philo->time_of_last_meal = ft_gettime();
		philo->number_of_eat++;
		check_number_of_meal(philo, info);
		pthread_mutex_lock(&info->mutex);
		print_status(philo, info);
		pthread_mutex_unlock(&info->mutex);
		usleep(info->time_to_eat * 1000);
		drop_forks(philo, info);
		return (1);
	}
	else
		usleep(50);
	return (0);
}
