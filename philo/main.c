/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:59:37 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/09 16:42:17 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (ft_error_msg(1));
	if (ft_check_input(av))
		return (ft_error_msg(2));
	if (ft_init_table(&table, av))
		return (2);

}

int	ft_init_table(t_table *table, char **av)
{
	table->num_phil = ft_atol(av[1]);
	table->time_2die = ft_atol(av[2]);
	table->time_2eat = ft_atol(av[3]);
	table->time_2sleep = ft_atol(av[4]);
	if (av[5])
		table->num_meals = ft_atol(av[5]);
	return (0);
}

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

int	ft_error_msg(int code)
{
	if (code == 1)
		printf("Error: Wrong number of arguments\n");
	if (code == 2)
		printf("Error: Wrong arguments format, please insert a positive int\n");
	return (code);
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
