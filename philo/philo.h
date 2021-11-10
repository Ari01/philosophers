/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:08:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/10 01:37:08 by dchheang         ###   ########.fr       */
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
# define FORK		1
# define EATING		2
# define SLEEPING	3
# define DIED		4

/**********************	STRUCT ************************/

typedef	struct	s_fork
{
	int				status;
	pthread_mutex_t	mutex;
}	t_fork;

typedef	struct	s_info
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_eat;
	int				all_ate_count;
	int				philosopher_died;
	int				current_philosopher;
	unsigned long	time_start;
	t_fork			*forks;
	pthread_mutex_t	mutex;
}	t_info;

typedef struct	s_philosopher
{
	int				number;
	int				left;
	int				right;
	int				status;
	int				number_of_eat;
	unsigned long	time_of_last_meal;
}	t_philosopher;

/**********************	FUNCTIONS ************************/

/*	UTILS	*/
unsigned long	ft_gettime();
float			get_timediff(unsigned long t1, unsigned long t2);
int				ft_atoi(char *s);
int				ft_strlen(char *s);

/*	PRINT	*/
void			print_msg(char *s);
void			print_status(unsigned long timestamp, t_philosopher philo);
void			print_info(t_info *info);

/*	THREADS	*/
pthread_t		*init_threads(t_info *info);
int				wait_threads(pthread_t *threads, int nthreads);

/*	PHILO	*/
int				init_philosopher(t_philosopher *philo, t_info *info);
void			simulate(t_philosopher *philo, t_info *info);

/*	ACTIONS	*/
int				die(t_philosopher *philo, t_info *info);

#endif
