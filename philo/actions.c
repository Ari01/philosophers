/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 06:13:11 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/18 11:01:02 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo, t_info *info)
{
	pthread_mutex_lock(&info->fork[philo->lf]);
	pthread_mutex_lock(&info->fork[philo->rf]);
	print_action(philo, info, "has taken a fork");
	print_action(philo, info, "has taken a fork");
}

void	drop_forks(t_philosopher *philo, t_info *info)
{
	pthread_mutex_unlock(&info->fork[philo->lf]);
	pthread_mutex_unlock(&info->fork[philo->rf]);
}

void	eat(t_philosopher *philo, t_info *info)
{
	if (info->n_philo == 1)
		return ;
	take_forks(philo, info);
	pthread_mutex_lock(&info->eat_mutex);
	print_action(philo, info, "is eating");
	philo->t_last_meal = get_time();
	philo->n_eat++;
	pthread_mutex_unlock(&info->eat_mutex);
	ft_sleep(info->time_to_eat, info);
	drop_forks(philo, info);
	philo->status = EATING;
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
