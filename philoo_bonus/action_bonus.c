/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:50:44 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/27 19:46:52 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

unsigned long	current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print(t_philosopher *p, char *msg, int id)
{
	sem_wait(p->write_lock);
	printf(msg, current_time_in_ms() - p->t0, id + 1);
	sem_post(p->write_lock);
}

void	use_usleep(unsigned long time_activities)
{
	unsigned long	t_zero;

	t_zero = current_time_in_ms();
	while (current_time_in_ms() - t_zero < time_activities)
		usleep(100);
}
