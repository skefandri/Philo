/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:48:55 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/17 17:27:56 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	init(t_philosopher *p, char **argv, int argc)
{
	int	i;

	i = 0;
	p->num_philosophers = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		p->number_meals = -1;
	if (argc == 6)
		p->number_meals = ft_atoi(argv[5]);
	p->meals_eating = 0;
}

void	*philosophers_semaphore(t_philosopher *p)
{
	pthread_t	check_dead;

	p->t0 = (p->last_eat.tv_sec * 1000 + p->last_eat.tv_usec / 1000);
	if (p->id % 2)
		use_usleep(p->time_to_eat / 2);
	pthread_create(&check_dead, NULL, (void *)check_death, p);
	while (1)
	{
		sem_wait(p->forks);
		print(p, "%ld ms: %d take a fork\n", p->id);
		sem_wait(p->forks);
		print(p, "%ld ms: %d take a fork\n", p->id);
		print(p, "%ld ms: %d is eating\n", p->id);
		gettimeofday(&p->last_eat, NULL);
		use_usleep(p->time_to_eat);
		sem_post(p->forks);
		sem_post(p->forks);
		p->meals_eating++;
		if (p->number_meals != -1 && p->meals_eating == p->number_meals)
			exit (0);
		print(p, "%ld ms: %d is sleeping\n", p->id);
		use_usleep(p->time_to_sleep);
		print(p, "%ld ms: %d is thinking\n", p->id);
	}
	return (NULL);
}

int	check_death(t_philosopher *p)
{
	while (1)
	{
		if (current_time_in_ms()
			- (p->last_eat.tv_sec * 1000 + p->last_eat.tv_usec / 1000)
			>= (unsigned long)p->time_to_die)
		{
			sem_wait(p->write_lock);
			printf("%ld ms: %d is die\n",
				current_time_in_ms() - p->t0, p->id + 1);
			exit (1);
		}
		usleep(300);
	}
}

void	init_process(t_philosopher *philosophers)
{
	int		i;
	sem_t	*forks;
	sem_t	*write_lock;

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	forks = sem_open("/forks", O_CREAT, 0644, philosophers->num_philosophers);
	write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	while (i < philosophers->num_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].forks = forks;
		philosophers[i].write_lock = write_lock;
		philosophers[i].time_to_eat = philosophers[0].time_to_eat ;
		philosophers[i].time_to_sleep = philosophers[0].time_to_sleep;
		philosophers[i].time_to_die = philosophers[0].time_to_die;
		philosophers[i].number_meals = philosophers[0].number_meals;
		i++;
	}
	gettimeofday(&philosophers->last_eat, NULL);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philosophers;

	check_arguments(argc);
	if (check_errors(argc, argv))
		return (1);
	philosophers = create_philosophers(argv);
	init(philosophers, argv, argc);
	init_process(philosophers);
	fork_and_start_philosophers(philosophers);
	handle_processes(philosophers);
	return (0);
}
