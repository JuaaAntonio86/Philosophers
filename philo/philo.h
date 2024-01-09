/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-anm  <juan-anm@student.42barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:41:15 by juanantonio       #+#    #+#             */
/*   Updated: 2024/01/09 15:33:42 by juan-anm         ###   ########.fr       */
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
	long	num_phil;
	long	time_2die;
	long	time_2eat;
	long	time_2sleep;
	long	num_meals;

}	t_table;

int		ft_error_msg(int code);
int		ft_init_table(t_table *table, char **av);
int		ft_check_input(char **av);
long	ft_atol(const char *str);

#endif
