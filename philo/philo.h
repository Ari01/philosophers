/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:08:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/06 20:51:33 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>


/**********************	CONST ************************/

/*	FORK STATE	*/
# define AVAILABLE	0
# define BUSY		1

/* PHILOSOPHER STATE	*/
# define THINKING	0
# define EATING		1
# define SLEEPING	2
# define DEAD		3

/**********************	STRUCT ************************/

typedef	struct	s_fork
{
	int				state;
	pthread_mutex_t	mutex;
}	t_fork;

typedef	struct	s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				all_ate_count;
	int				philosopher_died;
	int				current_philosopher;
	struct timeval	time_start;
	t_fork			*forks;
	pthread_mutex_t	mutex;
}	t_info;

typedef struct	s_philosopher
{
	int			number;
	int			status;
	int			number_of_eat;
	long int	time_of_last_meal;
}	t_philosopher;

/**********************	FUNCTIONS ************************/

/*	UTILS	*/
int			ft_atoi(char *s);
int			ft_strlen(char *s);

/*	PRINT	*/
void		print_msg(char *s);
void		print_status(int status);
void		print_info(t_info *info);

/*	THREADS	*/
pthread_t	*init_threads(t_info *info);
int			wait_threads(pthread_t *threads, int nthreads);

#endif
