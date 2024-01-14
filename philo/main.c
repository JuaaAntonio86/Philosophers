/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:59:37 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/12 19:31:14 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*test(void *thread)
{
	t_philo	*philosopher = (t_philo *)thread;
	t_table *table = philosopher->table;

	if (philosopher->id % 2 == 0)
		usleep(table->time_2eat / 3);
	pthread_mutex_lock(&(table->forks[philosopher->l_fork]));	
	pthread_mutex_lock(&(table->forks[philosopher->r_fork]));	
	int i = 0;
	while (i++< 1000)
		table->num_meals++;
	printf("number %li with id %i\n", table->num_meals, philosopher->id);
	pthread_mutex_unlock(&(table->forks[philosopher->l_fork]));	
	pthread_mutex_unlock(&(table->forks[philosopher->r_fork]));	

	return (NULL);
}

static	int	create_table(t_table *table)
{
	int i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->num_phil);
	if (!table->philos)
		return (ft_error_msg(3));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_phil);
	if (!table->forks)
		return (ft_error_msg(3));
	while (++i < table->num_phil)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (ft_error_msg(3));
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].l_fork = i + 1;
		if (i == 0)
			table->philos[i].r_fork = table->num_phil;
		else
			table->philos[i].r_fork = i;
		pthread_create(&(table->philos[i].thread_id), NULL, test, &(table->philos[i]));
	}
	i = -1;
	while (++i < table->num_phil)
	{
		pthread_join((table->philos[i].thread_id), NULL);
		pthread_mutex_destroy(&(table->forks[i]));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (ft_error_msg(1));
	if (ft_check_input(av))
		return (ft_error_msg(2));
	if (ft_init_table(&table, av))
		return (ft_error_msg(2));
	if (create_table(&table))
		return (3);
	return (0);
}

int	ft_init_table(t_table *table, char **av)
{
	table->num_phil = ft_atol(av[1]);
	table->time_2die = ft_atol(av[2]);
	table->time_2eat = ft_atol(av[3]);
	table->time_2sleep = ft_atol(av[4]);
	if (table->num_phil < 2 || table->time_2die < 1 
		|| table->time_2eat < 1 || table->time_2sleep < 1)
		return (1);
	if (av[5])
		table->num_meals = ft_atol(av[5]);
	else
		table->num_meals = -1;
	return (0);
}

