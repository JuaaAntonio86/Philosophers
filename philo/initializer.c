/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm <juan-anm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:07:47 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/17 17:02:06 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_table(t_table *table, char **av)
{
	table->num_phil = ft_atol(av[1]);
	table->time_2die = ft_atol(av[2]);
	table->time_2eat = ft_atol(av[3]);
	table->time_2sleep = ft_atol(av[4]);
	table->end_dinner = 0;
	table->all_ate = 0;
	if (table->num_phil < 1 || table->time_2die < 1
		|| table->time_2eat < 1 || table->time_2sleep < 1)
		return (1);
	if (table->num_phil > 200 || table->time_2die > INT_MAX
		|| table->time_2eat > INT_MAX || table->time_2sleep > INT_MAX)
		return (1);
	if (av[5])
	{
		table->meals_input = ft_atol(av[5]);
		if (table->meals_input < 1 || table->meals_input > INT_MAX)
			return (1);
	}
	else
		table->meals_input = -1;
	return (0);
}

int	mutex_initializer(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(table->printing), NULL))
		return (ft_error_msg(4));
	if (pthread_mutex_init(&(table->meal_update), NULL))
		return (ft_error_msg(4));
	while (++i < table->num_phil)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (ft_error_msg(4));
	}
	return (0);
}

int	philo_initializer(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_phil)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].num_meals = 0;
		table->philos[i].r_fork = i;
		if (i == table->num_phil - 1)
			table->philos[i].l_fork = 0;
		else
			table->philos[i].l_fork = i + 1;
		table->philos[i].last_meal = timestamp();
		if (pthread_create(&(table->philos[i].thread_id), NULL, \
			&eats, &(table->philos[i])))
			return (ft_error_msg(5));
	}
	return (0);
}
