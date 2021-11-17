/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 06:13:11 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/17 16:57:21 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philosopher *philo, t_info *info)
{
	t_fork	*lf;
	t_fork	*rf;
	int		ret;

	ret = 0;
	lf = &info->fork[philo->lf];
	rf = &info->fork[philo->rf];
	pthread_mutex_lock(&lf->mutex);
	pthread_mutex_lock(&rf->mutex);
	if (lf->is_available && rf->is_available)
	{
		print_action(philo, info, "has taken a fork");
		print_action(philo, info, "has taken a fork");
		lf->is_available = 0;
		rf->is_available = 0;
		ret = 1;
	}
	return (ret);
}

void	drop_forks(t_philosopher *philo, t_info *info)
{
	t_fork	*lf;
	t_fork	*rf;

	lf = &info->fork[philo->lf];
	rf = &info->fork[philo->rf];
	lf->is_available = 1;
	rf->is_available = 1;
	pthread_mutex_unlock(&lf->mutex);
	pthread_mutex_unlock(&rf->mutex);
}

void	eat(t_philosopher *philo, t_info *info)
{
	if (info->n_philo == 1)
		return ;
	if (take_forks(philo, info))
	{
		print_action(philo, info, "is eating");
		pthread_mutex_lock(&info->eat_mutex);
		philo->t_last_meal = get_time();
		philo->n_eat++;
		pthread_mutex_unlock(&info->eat_mutex);
		ft_sleep(info->time_to_eat, info);
		drop_forks(philo, info);
		philo->status = EATING;
	}
}

void	rest(t_philosopher *philo, t_info *info)
{
	print_action(philo, info, "is sleeping");
	ft_sleep(info->time_to_sleep, info);
	philo->status = SLEEPING;
}

void	think(t_philosopher *philo, t_info *info)
{
	print_action(philo, info, "is thinking");
	philo->status = THINKING;
}

