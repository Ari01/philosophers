/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 05:01:57 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/18 10:15:59 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_philo(void *arg)
{
	t_info			*info;
	t_philosopher	*philo;

	info = (t_info *)arg;
	philo = &info->philo[info->current_philo];
	info->current_philo++;
	while (!info->end_sim)
	{
		if (philo->status == THINKING)
		{
			eat(philo, info);
			if (info->all_ate)
				break ;
		}
		else if (philo->status == EATING)
			rest(philo, info);
		else if (philo->status == SLEEPING)
			think(philo, info);
	}
	return (NULL);
}

pthread_t	*init_threads(t_info *info)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = malloc(sizeof(*thread) * (info->n_philo + 1));
	if (!thread)
		return (NULL);
	info->t_start = get_time();
	while (i < info->n_philo)
	{
		info->philo[i].t_last_meal = get_time();
		if (pthread_create(&thread[i], NULL, run_philo, info))
		{
			free(thread);
			return (NULL);
		}
		i++;
	}
	if (pthread_create(&thread[i], NULL, check_end_sim, info))
	{
		free(thread);
		return (NULL);
	}
	return (thread);
}

int	wait_threads(pthread_t *thread, int n_thread)
{
	int	i;

	i = 0;
	while (i < n_thread)
	{
		if (pthread_join(thread[i], NULL))
		{
			free(thread);
			return (0);
		}
		i++;
	}
	return (1);
}

int	run(t_info *info)
{
	pthread_t	*thread;

	thread = init_threads(info);
	if (!thread)
		return (0);
	if (!wait_threads(thread, info->n_philo + 1))
		return (0);
	free(thread);
	return (1);
}
