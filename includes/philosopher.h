/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:26:21 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/18 22:02:08 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philosopher
{
	pthread_t		*t;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned long	*last_eat;
	int				num_philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	w;
	int				number_meals;
	int				*eat_count;
	int				meals_eating;
	pthread_mutex_t	incr;
	pthread_mutex_t	ccc;
	pthread_mutex_t	check;
	time_t			t0;
	int				is_alive;
}	t_philosopher;

void			think(t_philosopher *p);
int				is_integer(char *str);
int				str_to_int(char *str);
int				check_errors(int argc, char **argv);
void			eat(t_philosopher *p);
void			die(t_philosopher *p);
void			sleep_philosopher(t_philosopher *p);
void			*philosopher_thread(void *data);
int				ft_atoi(const char *str);
unsigned long	current_time_in_ms(void);
int				check_death(t_philosopher *p);
void			use_usleep(unsigned long time_activities);
void			print(t_philosopher *p, char *msg, int id);
void			get_forks(pthread_mutex_t *right,
					pthread_mutex_t *left, t_philosopher *p, int id);

#endif
