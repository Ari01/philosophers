/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:44:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/06 20:52:13 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	init_philosopher(t_info *info)
{
	t_philosopher	philo;

	philo.number = info->current_philosopher;
	info->current_philosopher++;
	philo.status = THINKING;
	philo.number_of_eat = 0;
	philo.time_of_last_meal = info->time_start.tv_usec;
	return (philo);
}

void	*run_thread(void *arg)
{
	t_info			*info;
	t_philosopher	philo;

	info = (t_info *)arg;
	pthread_mutex_lock(&info->mutex);
	philo = init_philosopher(info);
	pthread_mutex_unlock(&info->mutex);
	return (NULL);
}

pthread_t	*init_threads(t_info *info)
{
	int			i;
	int			ret;
	pthread_t	*threads;

	i = 0;
	ret = 0;
	threads = malloc(sizeof(*threads) * info->number_of_philosophers);
	if (!threads)
		return (NULL);
	if (gettimeofday(&info->time_start, NULL))
		return (NULL);
	while (i < info->number_of_philosophers)
	{
		ret = pthread_create(&threads[i], NULL, run_thread, info);
		if (ret)
			return (NULL);
		i++;
	}
	return (threads);
}

int	wait_threads(pthread_t *threads, int nthreads)
{
	int	i;
	int	ret;

	i = 0;
	while (i < nthreads)
	{
		ret = pthread_join(threads[i], NULL);
		if (ret)
			return (0);
		i++;
	}
	return (1);
}
