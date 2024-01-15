/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:59:37 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/15 18:57:09 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool ft_check_all_ate(t_table *table)
// {
// 	int	i;
// 	static	int lunches = 0;

// 	i = 0;
// 	if (table->meals_input == -1)
// 		return (0);
// 	while (i < table->num_phil)
// 	{
// 		if (table->philos[i].num_meals == table->meals_input)
// 			lunches++;
// 		if (lunches == table->meals_input)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// static void	*waiter_work(void *table)
// {
// 	while (!ft_check_all_ate(table))
// 		;
// 	printf("Dinner has finished");
// 	return (NULL);
// }

void	*eats(void *thread)
{
	t_philo		*philo;
	t_table		*table;
	long long	time;

	philo = (t_philo *)thread;
	table = philo->table;
	if (philo->id % 2 != 0)
		usleep(table->time_2eat / 2);
	while (42)
	{
		pthread_mutex_lock(&(table->forks[philo->l_fork]));
		ft_blockprint(table, "has taken a fork", philo->id);
		pthread_mutex_lock(&(table->forks[philo->r_fork]));
		ft_blockprint(table, "has taken a fork", philo->id);
		time = timestamp();
		ft_blockprint(table, "is eating", philo->id);
		while (table->time_2eat >= timestamp() - time)
			;
		philo->last_meal = timestamp();
		philo->num_meals++;
		pthread_mutex_unlock(&(table->forks[philo->l_fork]));
		pthread_mutex_unlock(&(table->forks[philo->r_fork]));
		usleep(200);
		if (philo->num_meals == table->meals_input)
			break ;
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
	//pthread_create(&(table->waiter), NULL, waiter_work, &(table));
	//waiter_work(&table);
	i = -1;
	while (++i < table->num_phil)
	{
		pthread_join((table->philos[i].thread_id), NULL);
		pthread_mutex_destroy(&(table->forks[i]));
	}
	pthread_mutex_destroy(&(table->printing));
	//pthread_join((table->waiter), NULL);
	return (0);
}

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
