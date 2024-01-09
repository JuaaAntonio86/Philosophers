/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:41:15 by juanantonio       #+#    #+#             */
/*   Updated: 2024/01/09 14:09:32 by juan-anm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	int	id;
	int	last_meal;

}	t_philo;

typedef struct s_table
{
	int	num_phil;
	int	time_2die;
	int	time_2eat;
	int	time_2sleep;
	int	num_meals;

}	t_table;

int		ft_error_msg(int code);
int		ft_parse_arg(t_table *table, char **av);
int		ft_check_input(char **av);


#endif
