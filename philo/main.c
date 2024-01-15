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

bool ft_check_all_ate(t_table *table)
{


}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_blockprint(t_table *table, char *str, int philo)
{
	pthread_mutex_lock(&(table->printing));
	printf("Time %lli", timestamp() - table->dinner_time);
	printf(" Philosopher number %i %s\n", philo, str);
	pthread_mutex_unlock(&(table->printing));
}
static void *waiter_work(void *table)
{
	while(!ft_check_all_ate(&table)) //|| !ft_check_deads(&table))
	{


	}

}

static void	*test(void *thread)
{
	t_philo	*philosopher = (t_philo *)thread;
	t_table *table = philosopher->table;

	if (philosopher->id % 2 == 0)
		usleep(250);
	pthread_mutex_lock(&(table->forks[philosopher->l_fork]));
	ft_blockprint(table, "has taken a fork", philosopher->id);
	pthread_mutex_lock(&(table->forks[philosopher->r_fork]));
	ft_blockprint(table, "has taken a fork", philosopher->id);
	ft_blockprint(table, "is eating", philosopher->id);
	while(table->time_2eat >= timestamp() - philosopher->last_meal)
		;
	philosopher->num_meals++;
	pthread_mutex_unlock(&(table->forks[philosopher->l_fork]));	
	pthread_mutex_unlock(&(table->forks[philosopher->r_fork]));	
	philosopher->last_meal = timestamp();
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
	table->dinner_time = timestamp();
	while (++i < table->num_phil)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (ft_error_msg(3));
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].l_fork = i + 1;
		table->philos[i].num_meals = 0;
		table->philos[i].last_meal = timestamp();
		if (i == 0)
			table->philos[i].r_fork = table->num_phil;
		else
			table->philos[i].r_fork = i;
		pthread_create(&(table->philos[i].thread_id), NULL, test, &(table->philos[i]));
	}
	pthread_create(&(table->waiter), NULL, waiter_work, &(table));
	i = -1;
	while (++i < table->num_phil)
	{
		pthread_join((table->philos[i].thread_id), NULL);
		pthread_mutex_destroy(&(table->forks[i]));
	}
	pthread_join((table->waiter), NULL);
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
		table->meals_input = ft_atol(av[5]);
	else
		table->meals_input = -1;
	pthread_mutex_init(&(table->printing), NULL);
	return (0);
}

