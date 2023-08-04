/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:16:27 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/17 15:19:51 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	check_arguments(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments\n");
		exit(1);
	}
}

t_philosopher	*create_philosophers(char **argv)
{
	t_philosopher	*philosophers;

	philosophers = malloc(sizeof(t_philosopher) * ft_atoi(argv[1]));
	return (philosophers);
}

void	fork_and_start_philosophers(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->num_philosophers)
	{
		philosophers[i].last_eat = philosophers[0].last_eat;
		philosophers[i].pid = fork();
		if (philosophers[i].pid == -1)
		{
			while (--i >= 0)
				kill(philosophers[i].pid, SIGTERM);
			exit(1);
		}
		if (philosophers[i].pid == 0)
			philosophers_semaphore(&philosophers[i]);
		i++;
	}
}

void	handle_processes(t_philosopher *philosophers)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (wait(&status) != -1)
	{
		if (WEXITSTATUS(status))
			while (i < philosophers->num_philosophers)
				kill(philosophers[i++].pid, SIGTERM);
	}
}
