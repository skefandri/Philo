/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 21:37:20 by ysabr             #+#    #+#             */
/*   Updated: 2023/08/04 16:01:34 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

unsigned long	current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_philosopher *p, char *msg, int id)
{
	pthread_mutex_lock(&p->w);
	printf(msg, current_time_in_ms() - p->t0, id + 1);
	pthread_mutex_unlock(&p->w);
}

void	use_usleep(unsigned long time_activities)
{
	time_t	t_zero;

	t_zero = current_time_in_ms();
	while (current_time_in_ms() - t_zero < time_activities)
		usleep(100);
}

void	get_forks(pthread_mutex_t *right
	, pthread_mutex_t *left, t_philosopher *p, int id)
{
	pthread_mutex_lock(right);
	print(p, "%ld ms: %d take a fork\n", id);
	pthread_mutex_lock(left);
	pthread_mutex_lock(&p->incr);
	p->last_eat[id] = current_time_in_ms();
	pthread_mutex_unlock(&p->incr);
	print(p, "%ld ms: %d take a fork\n", id);
	print(p, "%ld ms: %d is eating\n", id);
	use_usleep(p->time_to_eat);
}
