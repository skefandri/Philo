/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:21:44 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/17 17:26:09 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_philosopher
{
	pid_t			pid;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	struct timeval	last_eat;
	int				num_philosophers;
	int				number_meals;
	sem_t			*forks;
	int				meals_eating;
	unsigned long	t0;
	sem_t			*write_lock;
}	t_philosopher;

void			*philosophers_semaphore(t_philosopher *p);
void			init(t_philosopher *p, char **argv, int argc);
int				ft_atoi(const char *str);
unsigned long	current_time_in_ms(void);
void			init_process(t_philosopher *philosophers);
int				check_death(t_philosopher *p);
void			check_arguments(int argc);
void			fork_and_start_philosophers(t_philosopher *philosophers);
t_philosopher	*create_philosophers(char **argv);
void			handle_processes(t_philosopher *philosophers);
void			use_usleep(unsigned long time_activities);
void			print(t_philosopher *p, char *msg, int id);
int				ft_strlen(char *str);
int				is_integer(char *str);
int				errmsg(char *str);
int				str_to_int(char *str);
int				check_errors(int argc, char **argv);

#endif