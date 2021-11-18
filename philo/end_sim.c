/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:29:37 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/18 11:00:51 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_info *info)
{
	int					i;
	int					ret;
	unsigned long long	timediff;
	unsigned long long	time_to_die;

	i = 0;
	ret = 0;
	while (i < info->n_philo && !info->end_sim)
	{
		pthread_mutex_lock(&info->eat_mutex);
		timediff = get_timediff(info->philo[i].t_last_meal);
		time_to_die = (unsigned long long)info->time_to_die;
		if (timediff >= time_to_die)
		{
			print_action(&info->philo[i], info, "died");
			info->end_sim = 1;
			info->philo[i].status = DEAD;
			ret = 1;
		}
		pthread_mutex_unlock(&info->eat_mutex);
		i++;
	}
	return (ret);
}

int	check_all_eat(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo && info->philo[i].n_eat >= info->n_eat)
		i++;
	if (i >= info->n_philo)
	{
		info->end_sim = 1;
		return (1);
	}
	return (0);
}

void	*check_end_sim(void *arg)
{
	t_info	*info;

	info = (t_info *)arg;
	while (1)
	{
		if (check_death(info))
			return (NULL);
		if (info->n_eat != -1 && check_all_eat(info))
			return (NULL);
	}
	return (NULL);
}
