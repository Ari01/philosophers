/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:08:44 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/16 13:53:02 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

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

typedef struct	s_list
{
	int				value;
	struct s_list	*next;
}	t_list;

typedef struct s_fork
{
	int				status;
	t_list			*queue;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_info
{
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_eat;
	int				all_ate_count;
	int				philosopher_died;
	int				current_philosopher;
	struct timeval	time_start;
	int				turn;
	t_fork			*forks;
	pthread_mutex_t	mutex;
}	t_info;

typedef struct s_philosopher
{
	int				number;
	t_fork			*lf;
	t_fork			*rf;
	int				status;
	int				number_of_eat;
	struct timeval	time_of_last_meal;
}	t_philosopher;

/**********************	FUNCTIONS ************************/

/*	UTILS	*/
struct timeval	ft_gettime(void);
float			get_timediff(struct timeval start);
int				ft_atoi(char *s);
int				ft_strlen(char *s);

/*	PRINT	*/
void			print_msg(char *s);
void			print_status(t_philosopher *philo, t_info *info);
void			print_info(t_info *info);

/*	THREADS	*/
pthread_t		*init_threads(t_info *info);
int				wait_threads(pthread_t *threads, int nthreads);

/*	PHILO	*/
t_philosopher	init_philosopher(t_info *info);
void			simulate(t_philosopher *philo, t_info *info);

/*	ACTIONS	*/
int				die(t_philosopher *philo, t_info *info);
int				eat(t_philosopher *philo, t_info *info);
void			rest(t_philosopher *philo, t_info *info);
void			think(t_philosopher *philo, t_info *info);

/*	LIST	*/
t_list			*ft_lstnew(int value);
void			ft_lstadd_back(t_list **head, t_list *new);
int				ft_lstfind(t_list *list, int value);
void			ft_lstremove(t_list **list, int to_remove);

#endif
