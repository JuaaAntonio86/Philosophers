/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm <juan-anm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:59:37 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/17 17:12:43 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_all_ate(t_table *table)
{
	int			i;
	static int	lunches = 0;

	i = 0;
	if (table->meals_input == -1)
		return (0);
	while (i < table->num_phil)
	{
		if (table->philos[i].num_meals == table->meals_input)
			lunches++;
		if (lunches == table->num_phil)
		{
			table->all_ate = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

inline int	ft_check_all_live(t_table *table)
{
	int			i;
	long long	time;

	i = 0;
	while (!table->all_ate && !table->end_dinner && i < table->num_phil)
	{
		pthread_mutex_lock(&(table->meal_update));
		time = timestamp() - table->philos[i].last_meal;
		pthread_mutex_unlock(&(table->meal_update));
		if (time > table->time_2die)
		{
			table->end_dinner = table->philos[i].id + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*waiter_work(t_table *table)
{
	while (!ft_check_all_ate(table) && !ft_check_all_live(table))
		ft_usleep(10);
	return (NULL);
}

void	*eats(void *thread)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)thread;
	table = philo->table;
	if (philo->id % 2 || philo->id == table->num_phil)
		ft_usleep(table->time_2eat);
	while (!table->end_dinner && !table->all_ate)
	{
		philo_eat(table, philo);
	}
	return (NULL);
}

inline void	philo_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&(table->forks[philo->r_fork]));
	ft_blockprint(table, "has taken a fork", philo->id, 0);
	pthread_mutex_lock(&(table->forks[philo->l_fork]));
	ft_blockprint(table, "has taken a fork", philo->id, 0);
	ft_blockprint(table, "is eating", philo->id, 0);
	pthread_mutex_lock(&(table->meal_update));
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(table->meal_update));
	ft_usleep(table->time_2eat);
	philo->num_meals++;
	pthread_mutex_unlock(&(table->forks[philo->l_fork]));
	pthread_mutex_unlock(&(table->forks[philo->r_fork]));
	if (table->end_dinner || table->all_ate)
		return ;
	ft_blockprint(table, "is sleeping", philo->id, 0);
	ft_usleep(table->time_2sleep);
	ft_blockprint(table, "is thinking", philo->id, 0);
}
