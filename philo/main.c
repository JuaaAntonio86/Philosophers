/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm <juan-anm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:43:29 by juanantonio       #+#    #+#             */
/*   Updated: 2024/01/17 17:02:20 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		code;

	code = 0;
	if (ac != 5 && ac != 6)
		return (ft_error_msg(1));
	if (ft_check_input(av))
		return (ft_error_msg(2));
	if (ft_init_table(&table, av))
		return (ft_error_msg(2));
	code = mutex_initializer(&table);
	if (code)
		return (code);
	code = create_table(&table);
	if (code)
		return (code);
	return (0);
}

int	create_table(t_table *table)
{
	int	i;

	i = -1;
	table->dinner_time = timestamp();
	if (philo_initializer(table))
		return (5);
	waiter_work(table);
	i = -1;
	if (table->end_dinner)
		ft_blockprint(table, "has died", table->end_dinner - 1, 1);
	while (++i < table->num_phil)
	{
		pthread_mutex_unlock(&(table->forks[i]));
		pthread_mutex_destroy(&(table->forks[i]));
		pthread_join((table->philos[i].thread_id), NULL);
	}
	pthread_mutex_destroy(&(table->printing));
	pthread_mutex_destroy(&(table->meal_update));
	return (0);
}

int	ft_error_msg(int code)
{
	if (code == 1)
		printf("Error: Wrong number of arguments\n");
	if (code == 2)
		printf("Error: Wrong arguments format, please insert a positive int\n");
	if (code == 3)
		printf("Memory allocation failed.\n");
	if (code == 4)
		printf("Mutex initialization error.\n");
	if (code == 5)
		printf("Pthread initialization error.\n");
	return (code);
}
