/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:44:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/11 01:46:36 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_thread(void *arg)
{
	t_info			*info;
	t_philosopher	philo;

	info = (t_info *)arg;
	philo = init_philosopher(info);
	simulate(&philo, info);
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
	info->time_start = ft_gettime();
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
