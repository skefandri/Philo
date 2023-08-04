/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:52:10 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/07 13:52:10 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	sleep_and_think(t_philosopher *p, int id)
{
	pthread_mutex_lock(&p->incr);
	p->meals_eating++;
	print(p, "%ld ms: %d is sleeping\n", id);
	pthread_mutex_unlock(&p->incr);
	use_usleep(p->time_to_sleep);
	print(p, "%ld ms: %d is thinking\n", id);
}

void	*philosophers_threads(t_philosopher *p)
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	pthread_mutex_lock(&p->incr);
	id = p->id;
	pthread_mutex_unlock(&p->incr);
	right = p->forks + id;
	left =  p->forks + ((id + 1)% p->num_philosophers);
	while (1)
	{
		get_forks(right, left, p, id);
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		sleep_and_think(p, id);
	}
	return (NULL);
}

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
	p->forks = malloc(sizeof(pthread_mutex_t) * p->num_philosophers);
	while (i < p->num_philosophers)
		pthread_mutex_init(&p->forks[i++], NULL);
	pthread_mutex_init(&p->w, NULL);
	p->last_eat = malloc(sizeof(unsigned long) * p->num_philosophers);
	p->t = malloc(sizeof(pthread_t) * p->num_philosophers);
	p->t0 = current_time_in_ms();
	pthread_mutex_init(&p->incr, NULL);
	p->meals_eating = 0;
}

int	check_death(t_philosopher *p)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < p->num_philosophers)
		{
			pthread_mutex_lock(&p->incr);
			if (p->number_meals != -1
				&& p->meals_eating >= p->number_meals * p->num_philosophers)
				return (0);
			if (current_time_in_ms() - p->last_eat[i]
				>= (unsigned long)p->time_to_die)
			{
				pthread_mutex_lock(&p->w);
				printf("%ld ms: %d is die\n",
					current_time_in_ms() - p->t0, i + 1);
				return (1);
			}
			pthread_mutex_unlock(&p->incr);
		}
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	*philosophers;
	int				i;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	if (check_errors(argc, argv) || ft_atoi(argv[1]) <= 0)
		return (1);
	i = 0;
	philosophers = malloc(sizeof(t_philosopher) * ft_atoi(argv[1]));
	init(philosophers, argv, argc);
	while (i < philosophers->num_philosophers)
	{
		pthread_mutex_lock(&philosophers->incr);
		philosophers->id = i;
		philosophers->last_eat[i] = current_time_in_ms();
		pthread_mutex_unlock(&philosophers->incr);
		pthread_create(&philosophers->t[i], NULL,
			(void *)philosophers_threads, philosophers);
		usleep(100);
		i++;
	}
	return (check_death(philosophers));
}
