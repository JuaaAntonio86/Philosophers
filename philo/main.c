/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanantoniomartinezmorales <juanantonio    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:59:37 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/16 00:55:24 by juanantonio      ###   ########.fr       */
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

int	ft_check_all_live(t_table *table)
{
	int			i;
	long long	time;

	i = 0;
	while (!table->all_ate && !table->end_dinner && i < table->num_phil)
	{
		time = timestamp() - table->philos[i].last_meal;
		if (time > table->time_2die)
		{
			table->end_dinner = table->philos[i].id + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	*waiter_work(t_table *table)
{
	while (!ft_check_all_ate(table) && !ft_check_all_live(table))
		;
	return (NULL);
}

void	*eats(void *thread)
{
	t_philo		*philo;
	t_table		*table;
	long long	time;

	philo = (t_philo *)thread;
	table = philo->table;
	if (philo->id % 2 )
		usleep(1000);
	while (42)
	{
		pthread_mutex_lock(&(table->forks[philo->r_fork]));
		ft_blockprint(table, "has taken a fork", philo->id, 0);
		pthread_mutex_lock(&(table->forks[philo->l_fork]));
		ft_blockprint(table, "has taken a fork", philo->id, 0);
		time = timestamp();
		ft_blockprint(table, "is eating", philo->id, 0);
		philo->last_meal = timestamp();
		while (table->time_2eat >= timestamp() - time && !table->end_dinner)
			;
		philo->num_meals++;
		pthread_mutex_unlock(&(table->forks[philo->l_fork]));
		pthread_mutex_unlock(&(table->forks[philo->r_fork]));
		if (table->end_dinner || table->all_ate)
			break ;
		time = timestamp();
		ft_blockprint(table, "is sleeping", philo->id, 0);
		while (table->time_2sleep >= timestamp() - time && !table->end_dinner)
			;
		ft_blockprint(table, "is thinking", philo->id, 0);
		usleep(100);
	}
	return (NULL);
}

static	int	create_table(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->num_phil);
	if (!table->philos)
		return (ft_error_msg(3));
	table->dinner_time = timestamp();
	if (philo_initializer(table))
		return (5);
	waiter_work(table);
	i = -1;
	if (table->end_dinner)
		ft_blockprint(table, "has died", table->end_dinner - 1, 1);
	while (++i < table->num_phil)
	{
		pthread_join((table->philos[i].thread_id), NULL);
		pthread_mutex_destroy(&(table->forks[i]));
	}
	pthread_mutex_destroy(&(table->printing));
	return (0);
}

int	main(int ac, char **av)
{
	t_table	*table;
	int		code;

	code = 0;
	table = malloc(sizeof(t_table));
	if (ac != 5 && ac != 6)
		return (ft_error_msg(1));
	if (ft_check_input(av))
		return (ft_error_msg(2));
	if (ft_init_table(table, av))
		return (ft_error_msg(2));
	code = mutex_initializer(table);
	if (code)
		return (code);
	code = create_table(table);
	if (code)
		return (code);
	return (0);
}
