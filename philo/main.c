/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:08:19 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/11 01:10:18 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_info *info)
{
	if (pthread_mutex_init(&info->mutex, NULL))
	{
		print_msg("error initializing mutex\n");
		return (0);
	}
	if (info->number_of_philosophers <= 0 || info->time_to_die <= 0
		|| info->time_to_eat <= 0 || info->time_to_sleep <= 0)
	{
		print_msg("number of philosopher and timers can't be less or equal to 0\n");
		return (0);
	}
	return (1);
}

t_fork	*init_forks(int nforks)
{
	t_fork	*fork;
	int		i;

	i = 0;
	fork = malloc(sizeof(*fork) * nforks);
	if (!fork)
	{
		print_msg("error initializing forks\n");
		return (NULL);
	}
	while (i < nforks)
	{
		fork[i].status = AVAILABLE;
		if (pthread_mutex_init(&fork[i].mutex, NULL))
		{
			print_msg("error initializing fork mutex\n");
			free(fork);
			return (NULL);
		}
		i++;
	}
	return (fork);
}

unsigned long	get_time(char *arg)
{
	unsigned long	time;
	int				tmp;

	tmp = ft_atoi(arg);
	if (tmp <= 0)
		return (0);
	time = tmp;
	return (time);
}

int	get_args(int ac, char **av, t_info *info)
{
	info->forks = NULL;
	info->current_philosopher = 1;
	info->all_ate_count = 0;
	info->philosopher_died = 0;
	info->number_of_philosophers = ft_atoi(av[1]);
	info->time_to_die = get_time(av[2]);
	info->time_to_eat = get_time(av[3]);
	info->time_to_sleep = get_time(av[4]);
	if (ac == 6)
		info->number_of_eat = ft_atoi(av[5]);
	else
		info->number_of_eat = -1;
	if (!check_args(info))
		return (0);
	info->forks = init_forks(info->number_of_philosophers);
	if(!info->forks)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_info		info;
	pthread_t	*threads;

	if (ac != 5 && ac != 6)
	{
		print_msg("error args\n");
		return (1);
	}
	printf("getting arg\n");
	if (!get_args(ac, av, &info))
		return (1);
	printf("initializing threads\n");
	threads = init_threads(&info);
	if (!threads)
	{
		print_msg("error creating threads\n");
		return (1);
	}
	printf("waiting threads\n");
	if (!wait_threads(threads, info.number_of_philosophers))
	{
		print_msg("error waiting for threads to finish\n");
		return (1);
	}
	return (0);
}
