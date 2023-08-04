/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 10:54:32 by ysabr             #+#    #+#             */
/*   Updated: 2023/05/17 17:24:11 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	errmsg(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	str_to_int(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		return (0);
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	check_errors(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_integer(argv[i]))
		{
			errmsg("Error\n");
			return (1);
		}
		if (!str_to_int(argv[i]))
		{
			errmsg("Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}
