/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 14:31:25 by dchheang          #+#    #+#             */
/*   Updated: 2021/11/16 14:32:22 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	take_forks(t_philosopher *philo, t_info *info)
{
	int		ret;
	t_fork	*lf;
	t_fork	*rf;

	ret = 0;
	lf = philo->lf;
	rf = philo->rf;
	pthread_mutex_lock(&info->mutex);
	pthread_mutex_lock(&lf->mutex);
	pthread_mutex_lock(&rf->mutex);
	if (lf->status == AVAILABLE && rf->status == AVAILABLE)
	{
		if (check_queue(lf->queue, philo->number)
			&& check_queue(rf->queue, philo->number))
		{
			philo->status = FORK;
			print_status(philo, info);
			lf->status = BUSY;
			rf->status = BUSY;
			ret = 1;
			if (lf->queue)
				ft_lstremove(&lf->queue, philo->number);
			if (rf->queue)
				ft_lstremove(&rf->queue, philo->number);
		}
	}
	else
	{
		if (!ft_lstfind(lf->queue, philo->number))
			ft_lstadd_back(&lf->queue, ft_lstnew(philo->number));
		if (!ft_lstfind(rf->queue, philo->number))
			ft_lstadd_back(&rf->queue, ft_lstnew(philo->number));
	}
	pthread_mutex_unlock(&lf->mutex);
	pthread_mutex_unlock(&rf->mutex);
	pthread_mutex_unlock(&info->mutex);
	return (ret);
}

void	drop_forks(t_philosopher *philo, t_info *info)
{
	t_fork	*lf;
	t_fork	*rf;

	lf = philo->lf;
	rf = philo->rf;
	pthread_mutex_lock(&info->mutex);
	pthread_mutex_lock(&lf->mutex);
	pthread_mutex_lock(&rf->mutex);
	lf->status = AVAILABLE;
	rf->status = AVAILABLE;
	pthread_mutex_unlock(&lf->mutex);
	pthread_mutex_unlock(&rf->mutex);
	pthread_mutex_unlock(&info->mutex);
}
