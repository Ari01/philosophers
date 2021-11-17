/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 03:34:31 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/17 15:42:56 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/*********************** CONST *************************/

# define DEAD		0
# define THINKING	1
# define EATING		2
# define SLEEPING	3

/*********************** TYPES *************************/

typedef struct s_fork
{
	int				is_available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int					id;
	int					lf;
	int					rf;
	int					n_eat;
	int					status;
	unsigned long long	t_last_meal;
}	t_philosopher;

typedef struct s_info
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_eat;
	int					current_philo;
	int					end_sim;
	int					all_ate;
	unsigned long long	t_start;
	t_philosopher		*philo;
	t_fork				*fork;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		eat_mutex;
}	t_info;

/********************* FUNCTIONS ***********************/

/*	UTILS	*/
int					ft_atoi(char *s);
unsigned long long	get_time();
unsigned long long	get_timediff(unsigned long long start);
void				print_action(t_philosopher *philo, t_info *info, char *s);
void				ft_sleep(unsigned long long time, t_info *info);

/*	THREADS	*/
int					run(t_info *info);

/*	ACTIONS	*/
void				eat(t_philosopher *philo, t_info *info);
void				rest(t_philosopher *philo, t_info *info);
void				think(t_philosopher *philo, t_info *info);

#endif
