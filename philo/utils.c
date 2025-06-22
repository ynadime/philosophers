/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynadime <ynadime@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:49:35 by ynadime           #+#    #+#             */
/*   Updated: 2025/06/03 17:25:19 by ynadime          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long long	results;

	i = 0;
	sign = 1;
	results = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		results = (results * 10) + (str[i] - '0');
		if (results > INT_MAX || results < INT_MIN)
			return (0);
		i++;
	}
	return (results * sign);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
}

void	ft_sleep(size_t ms, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		if (simulation_ended(philo))
			break ;
		usleep(500);
	}
}
