/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanantonio <juanantonio@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:37:04 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/16 18:52:05 by juanantonio      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_input(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= 48 && av[i][j] <= 57)) 
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	ato;
	int		neg;

	ato = 0;
	neg = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ato = ato * 10;
		ato = ato + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		ato = ato * -1;
	return (ato);
}

void	ft_blockprint(t_table *table, char *str, int philo, int flag)
{
	if (!table->end_dinner || flag)
	{
		pthread_mutex_lock(&(table->printing));
		printf("Time %lli", timestamp() - table->dinner_time);
		printf(" Philosopher number %i %s\n", philo + 1, str);
		pthread_mutex_unlock(&(table->printing));
	}
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}
