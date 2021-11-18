/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 03:55:32 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/18 10:58:22 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_info(t_info info)
{
	if (info.n_philo <= 0)
		return (0);
	if (info.time_to_die <= 0)
		return (0);
	if (info.time_to_eat <= 0)
		return (0);
	if (info.time_to_sleep <= 0)
		return (0);
	return (1);
}

int	init_info(char **av, t_info *info)
{
	info->current_philo = 0;
	info->end_sim = 0;
	info->all_ate = 0;
	info->n_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		info->n_eat = ft_atoi(av[5]);
		if (info->n_eat <= 0)
			return (0);
	}
	else
		info->n_eat = -1;
	if (!check_info(*info))
		return (0);
	return (1);
}

int	init_philos(t_info *info)
{
	int	i;

	info->philo = malloc(sizeof(t_philosopher) * info->n_philo);
	if (!info->philo)
		return (0);
	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].lf = i;
		info->philo[i].rf = (i + 1) % info->n_philo;
		info->philo[i].n_eat = 0;
		info->philo[i].status = THINKING;
		i++;
	}
	return (1);
}

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->fork = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!info->fork)
		return (0);
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&info->eat_mutex, NULL))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 5 && ac != 6)
		printf("error: number of arguments\n");
	else if (!init_info(av, &info))
		printf("error: arguments\n");
	else if (!init_philos(&info) || !init_mutex(&info))
		printf("error: initializing info\n");
	else if (!run(&info))
		printf("error: threads\n");
	free(info.philo);
	free(info.fork);
	return (0);
}
