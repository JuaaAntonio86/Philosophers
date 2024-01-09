/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:59:37 by juan-anm          #+#    #+#             */
/*   Updated: 2024/01/09 14:09:19 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table table;

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return(ft_error_msg(1));
	if (ft_parse_arg(&table, av))
		return(2);

}

int	ft_parse_arg(t_table *table, char **av)
{
	(void) table;
	
	if (ft_check_input(av))
		return(ft_error_msg(2));
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
		printf("Error: Wrong number of arguments");
	if (code == 2)
		printf("Error: Wrong arguments format");
	return(code);
}