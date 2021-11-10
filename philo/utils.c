/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:09:33 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/10 01:36:03 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

unsigned long	ft_gettime()
{
	struct timeval	tv;
	unsigned long	time;

	if (gettimeofday(&tv, NULL))
	{
		print_msg("error getting time of day\n");
		return (0);
	}
	time = tv.tv_usec;
	return (time);
}

float	get_timediff(unsigned long t1, unsigned long t2)
{
	return (t1 - t2 + 0.001 * (t1 - t2));
}
