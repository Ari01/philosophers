/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 04:32:01 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/18 10:57:32 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	sign;
	int	n;

	n = 0;
	i = 0;
	sign = 1;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		n = n * 10 + (s[i++] - '0');
	return (n * sign);
}

unsigned long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long long	get_timediff(unsigned long long start)
{
	unsigned long long	end;

	end = get_time();
	return (end - start);
}

void	print_action(t_philosopher *philo, t_info *info, char *s)
{
	pthread_mutex_lock(&info->print_mutex);
	if (!info->end_sim)
		printf("%llu %d %s\n", get_timediff(info->t_start), philo->id, s);
	pthread_mutex_unlock(&info->print_mutex);
}

void	ft_sleep(unsigned long long time, t_info *info)
{
	unsigned long long	i;

	i = get_time();
	while (!info->end_sim)
	{
		if (get_timediff(i) >= time)
			break ;
		usleep(1);
	}
}
