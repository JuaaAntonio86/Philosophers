/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:37:04 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/11 18:11:09 by juan-anm         ###   ########.fr       */
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

int	ft_error_msg(int code)
{
	if (code == 1)
		printf("Error: Wrong number of arguments\n");
	if (code == 2)
		printf("Error: Wrong arguments format, please insert a positive int\n");
	if (code == 3)
		printf("Memory allocation failed.\n");
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
