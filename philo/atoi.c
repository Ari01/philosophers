/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:05:23 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/06 18:56:47 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\v' || c == '\f' ||
		c == '\r' || c == '\n' || c == ' ');
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	get_number(char *s, int i, int sign)
{
	int	start;
	int	n;
	int	ten;

	n = 0;
	ten = 1;
	start = i;
	while (ft_isdigit(s[i]))
		i++;
	while (--i >= start)
	{
		n += (s[i] - '0') * ten;
		ten *= 10;
	}
	n *= sign;
	return (n);
}

int	ft_atoi(char *s)
{
	int	n;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while(ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	n = get_number(s, i, sign);
	return (n);
}
