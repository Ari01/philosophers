/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:09:33 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/11 01:50:22 by dchheang         ###   ########.fr       */
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

struct timeval	ft_gettime()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		print_msg("error getting time of day\n");
	return (tv);
}

float	get_timediff(struct timeval start)
{
	struct timeval	end;
	float			ret;

	end = ft_gettime();
	ret = end.tv_sec - start.tv_sec + 1e-6 * (end.tv_usec - start.tv_usec);
	return (ret * 1000);
}
