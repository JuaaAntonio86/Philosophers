/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juanantoniomartinezmorales <juanantonio    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:41:15 by juanantonio       #+#    #+#             */
/*   Updated: 2024/01/16 23:39:37 by juanantonio      ###   ########.fr       */
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
	int					id;
	int					num_meals;
	long long			last_meal;
	pthread_t			thread_id;
	struct s_table		*table;
	int					l_fork;
	int					r_fork;
}				t_philo;

typedef struct s_table
{
	int					num_phil;
	int					time_2die;
	int					time_2eat;
	int					time_2sleep;
	int					meals_input;
	bool				all_ate;
	int					end_dinner;
	long long			dinner_time;
	pthread_t			waiter;
	pthread_mutex_t		meal_update;
	pthread_mutex_t		forks[200];
	pthread_mutex_t		printing;
	t_philo				philos[200];
}				t_table;

int			ft_error_msg(int code);
int			ft_init_table(t_table *table, char **av);
void		ft_blockprint(t_table *table, char *str, int philo, int flag);
int			ft_check_input(char **av);
long		ft_atol(const char *str);
long long	timestamp(void);
bool		ft_check_all_ate(t_table *table);
int			ft_check_all_live(t_table *table);
int			mutex_initializer(t_table *table);
int			philo_initializer(t_table *table);
void		*eats(void *thread);
void		*waiter_work(t_table *table);
int			create_table(t_table *table);
void		ft_usleep(int ms);
void		philo_eat(t_table *table, t_philo *philo);
#endif
